from pybricks.pupdevices import Motor
from pybricks.parameters import Port, Direction, Button, Axis
from pybricks.robotics import DriveBase
from pybricks.hubs import PrimeHub
from pybricks.tools import wait
from umath import sin, cos, atan2, sqrt, pi
from usys import stdin
from uselect import poll


FIRMWARE_VERSION = "2.1.0"
PROTOCOL_VERSION = 2

# 8 KB Flash allocatie: 12 slots x 640 bytes = 7680 bytes (+ 32 settings = 7712 bytes <= 8192)
MAX_SLOTS = 12
PROGRAM_BYTES = 640
SETTINGS_BYTES = 32
FLASH_TOTAL_BYTES = (MAX_SLOTS * PROGRAM_BYTES) + SETTINGS_BYTES

PROGRAM_MAGIC = b"Q3"   # Q3 zodat eventuele oude 40-byte Q2 rommel niet botst
SETTINGS_MAGIC = b"QCF3"

# DriveBase
WHEEL_DIAMETER_MM = 81.6
AXLE_TRACK_MM = 140

# Tracking / snapshots
SNAPSHOT_THRESHOLD_DEG = 10
SLOT_BROADCAST_INTERVAL_MS = 200  # alleen gebruikt als AUTO_SLOT_BROADCAST = True

# Oude positie van de "arm mode" knop in je huidige UI behouden voor compatibiliteit.
ARM_SLOT = 24

PORT_NAMES = ("A", "B", "C", "D", "E", "F")
DEFAULT_LEFT_DIRECTION = Direction.COUNTERCLOCKWISE
DEFAULT_RIGHT_DIRECTION = Direction.CLOCKWISE


# ============================================================
#  Hardware
# ============================================================

hub = PrimeHub()
hub.system.set_stop_button(None)

poller = poll()
poller.register(stdin)

left_motor = None
right_motor = None
robot = None

aux_motors = []
aux_last_angles = {}

# ============================================================
#  Systeemstatus
# ============================================================

current_slot = 0
arm_mode = False
tracking_mode = False
run_active = False
stop_requested = False
stop_arm_armed = False

slot_edit_buffer = [[] for _ in range(MAX_SLOTS)]
slot_has_program = [False] * MAX_SLOTS

x_pos = 0.0
y_pos = 0.0
last_distance = 0.0

# Tracking snapshot baseline: motornaam -> hoek
track_snapshot_baseline = {}
track_snapshot_ready = False

# Optionele "debug hold" is bewust niet actief buiten run.
manual_hold_requested = False
motor_hold_phase = 0
aux_hold_blocked = False

auto_slot_broadcast = False
last_slot_broadcast_ms = 0

# Wheel config (persistent)
wheel_left_port = "F"
wheel_left_inverted = False
wheel_right_port = "B"
wheel_right_inverted = False


# ============================================================
#  Kleine helpers
# ============================================================

def log_msg(msg):
    print("LOG|" + str(msg))


def clamp(v, lo, hi):
    if v < lo:
        return lo
    if v > hi:
        return hi
    return v


def beep(kind="ok"):
    # Kleine, niet-schreeuwerige feedback.
    try:
        if kind == "startup":
            hub.speaker.beep(880, 60)
        elif kind == "click":
            hub.speaker.beep(1040, 35)
        elif kind == "run":
            hub.speaker.beep(1320, 45)
        elif kind == "track":
            hub.speaker.beep(988, 40)
        elif kind == "save":
            hub.speaker.beep(1175, 45)
        elif kind == "error":
            hub.speaker.beep(220, 120)
        else:
            hub.speaker.beep(880, 30)
    except:
        pass


def s16_to_bytes(v):
    v = int(max(-32768, min(32767, v)))
    if v < 0:
        v += 65536
    return (v >> 8) & 255, v & 255


def bytes_to_s16(hi, lo):
    v = (int(hi) << 8) | int(lo)
    if v >= 32768:
        v -= 65536
    return v


def u16_to_bytes(v):
    v = int(max(0, min(65535, v)))
    return (v >> 8) & 255, v & 255


def bytes_to_u16(hi, lo):
    return (int(hi) << 8) | int(lo)


def port_from_name(name):
    return getattr(Port, name, None)


def port_index_from_name(name):
    name = str(name).upper().strip()
    if name in PORT_NAMES:
        return PORT_NAMES.index(name)
    return None


def port_name_from_index(idx):
    idx = int(idx)
    if 0 <= idx < len(PORT_NAMES):
        return PORT_NAMES[idx]
    return None


def parse_port_token(token):
    """
    Accepteert bijvoorbeeld:
      C
      Ei
      bI
    """
    token = str(token).strip()
    if not token:
        return None
    inverted = False
    if token[-1].lower() == "i":
        inverted = True
        token = token[:-1]
    token = token.upper()
    if token not in PORT_NAMES:
        return None
    return token, inverted


def format_port_token(name, inverted):
    return name + ("i" if inverted else "")


def default_direction_for_side(is_left):
    return DEFAULT_LEFT_DIRECTION if is_left else DEFAULT_RIGHT_DIRECTION


def opposite_direction(direction):
    return Direction.CLOCKWISE if direction == Direction.COUNTERCLOCKWISE else Direction.COUNTERCLOCKWISE


def direction_for_side(is_left, inverted):
    base = default_direction_for_side(is_left)
    return opposite_direction(base) if inverted else base


def storage_write(offset, data):
    try:
        hub.system.storage(int(offset), write=bytes(data))
        return True
    except Exception as e:
        print("ERR|STORAGE|WRITE|" + str(e))
        return False


def storage_read(offset, length):
    try:
        data = hub.system.storage(int(offset), read=int(length))
        if not data:
            return bytes([0] * int(length))
        if len(data) < length:
            data = data + b"\x00" * (length - len(data))
        return bytes(data[:length])
    except Exception:
        return bytes([0] * int(length))


def normalize_program_bytes(data):
    if not data:
        return bytes([0] * PROGRAM_BYTES)
    data = bytes(data[:PROGRAM_BYTES])
    if len(data) < PROGRAM_BYTES:
        data += b"\x00" * (PROGRAM_BYTES - len(data))
    return data


def program_offset(slot):
    return int(slot) * PROGRAM_BYTES


def settings_offset():
    return MAX_SLOTS * PROGRAM_BYTES


def slot_in_range(slot):
    try:
        slot = int(slot)
    except:
        return False
    return 0 <= slot < MAX_SLOTS


def safe_button_pressed():
    try:
        return set(hub.buttons.pressed())
    except:
        return set()


def maybe_poll_one_line():
    try:
        if poller.poll(0):
            raw = stdin.readline()
            if not raw:
                return None
            if isinstance(raw, bytes):
                raw = raw.decode()
            return raw.strip()
    except:
        return None
    return None


def read_all_pending(max_messages=8):
    count = 0
    while count < max_messages:
        line = maybe_poll_one_line()
        if line is None:
            return
        if line:
            verwerk_commando(line)
        count += 1


def request_stop():
    global stop_requested
    stop_requested = True


def service_runtime(max_messages=4):
    """
    Tijdens rijden / wachten wil je kleine inkomende commando's kunnen blijven verwerken.
    """
    read_all_pending(max_messages=max_messages)
    check_hardware_stop()
    hold_aux_motors_tick()


def hold_aux_motors_tick():
    global motor_hold_phase
    if not run_active:
        return
    if aux_hold_blocked:
        return
    if not aux_motors:
        return

    delta = 3 if motor_hold_phase == 0 else -3
    motor_hold_phase = 1 - motor_hold_phase

    for name, m in aux_motors:
        try:
            tgt = int(m.angle()) + delta
            try:
                m.track_target(tgt)
            except:
                try:
                    m.run_target(200, tgt)
                except:
                    pass
        except:
            pass


# ============================================================
#  Odometrie
# ============================================================

def update_odometrie():
    global x_pos, y_pos, last_distance
    afstand, _, _, _ = robot.state()
    delta = afstand - last_distance
    last_distance = afstand
    hoek = hub.imu.heading()
    rad = hoek * pi / 180
    x_pos += delta * cos(rad)
    y_pos += delta * sin(rad)
    return x_pos, y_pos, hoek


def reset_odometrie_naar_nul():
    global x_pos, y_pos, last_distance
    x_pos = 0.0
    y_pos = 0.0
    try:
        hub.imu.reset_heading(0)
    except:
        pass
    try:
        dist, _, _, _ = robot.state()
        last_distance = dist
    except:
        last_distance = 0.0
    log_msg("Positie gereset naar (0,0,0)")


def send_pose():
    x_nu, y_nu, h_nu = update_odometrie()
    msg = "POSE|{}|{}|{}".format(int(x_nu), int(y_nu), int(h_nu))
    print(msg)
    # compatibiliteit met je oude tooling
    print("WAYPOINT|{}|{}|{}".format(int(x_nu), int(y_nu), int(h_nu)))
    return x_nu, y_nu, h_nu


# ============================================================
#  Motor / wheel configuratie
# ============================================================

def wheel_cfg_string():
    return "{}{},{}{}".format(
        wheel_left_port,
        "i" if wheel_left_inverted else "",
        wheel_right_port,
        "i" if wheel_right_inverted else "",
    )


 
def save_settings():
    data = bytearray(SETTINGS_BYTES)
    for i in range(len(SETTINGS_MAGIC)):
        data[i] = SETTINGS_MAGIC[i]
    data[4] = PROTOCOL_VERSION & 255
    data[5] = port_index_from_name(wheel_left_port) or 0
    data[6] = 1 if wheel_left_inverted else 0
    data[7] = port_index_from_name(wheel_right_port) or 1
    data[8] = 1 if wheel_right_inverted else 0
    data[9] = current_slot & 255
    data[10] = 1 if auto_slot_broadcast else 0

    checksum = 0
    for b in data[:-1]:
        checksum = (checksum + b) & 255
    data[-1] = checksum

    ok = storage_write(settings_offset(), data)
    if ok:
        print("OK|SETTINGS|SAVED")
    return ok


def load_settings():
    global wheel_left_port, wheel_left_inverted, wheel_right_port, wheel_right_inverted
    global current_slot, auto_slot_broadcast

    data = storage_read(settings_offset(), SETTINGS_BYTES)
    if data[0:4] != SETTINGS_MAGIC:
        # defaults opslaan bij eerste boot of corrupte flash
        save_settings()
        return

    checksum = 0
    for b in data[:-1]:
        checksum = (checksum + b) & 255

    if checksum != data[-1]:
        print("ERR|SETTINGS|CHECKSUM")
        save_settings()
        return

    proto = data[4]
    if proto != PROTOCOL_VERSION:
        # Zelfde basis, maar versieverschil = toch proberen compatibel te blijven.
        pass

    left_idx = int(data[5])
    right_idx = int(data[7])

    left_name = port_name_from_index(left_idx)
    right_name = port_name_from_index(right_idx)

    if left_name is None:
        left_name = "F"
    if right_name is None:
        right_name = "B"

    if left_name == right_name:
        left_name, right_name = "F", "B"

    wheel_left_port = left_name
    wheel_right_port = right_name
    wheel_left_inverted = bool(data[6])
    wheel_right_inverted = bool(data[8])
    current_slot = int(data[9]) if slot_in_range(data[9]) else 0
    auto_slot_broadcast = bool(data[10])


def build_drivebase():
    global left_motor, right_motor, robot

    left_port_obj = port_from_name(wheel_left_port)
    right_port_obj = port_from_name(wheel_right_port)

    if left_port_obj is None or right_port_obj is None:
        raise ValueError("Ongeldige wielpoorten")

    if wheel_left_port == wheel_right_port:
        raise ValueError("Wielen mogen niet op dezelfde poort staan")

    # Oude objecten worden vervangen door nieuwe configuratie.
    left_motor = Motor(left_port_obj, direction_for_side(True, wheel_left_inverted))
    right_motor = Motor(right_port_obj, direction_for_side(False, wheel_right_inverted))

    robot = DriveBase(left_motor, right_motor, WHEEL_DIAMETER_MM, AXLE_TRACK_MM)


def discover_aux_motors():
    global aux_motors, aux_last_angles

    aux_motors = []
    aux_last_angles = {}

    excluded = {wheel_left_port, wheel_right_port}
    for name in PORT_NAMES:
        if name in excluded:
            continue
        port = port_from_name(name)
        if port is None:
            continue
        try:
            m = Motor(port)
            aux_motors.append((name, m))
            try:
                aux_last_angles[name] = int(m.angle())
            except:
                aux_last_angles[name] = 0
        except:
            pass


def capture_aux_angles():
    values = {}
    for name, m in aux_motors:
        try:
            values[name] = int(m.angle())
        except:
            values[name] = 0
    return values


def format_aux_angle_list(angle_map):
    bits = []
    for name in sorted(angle_map.keys()):
        bits.append("{}:{}".format(name, int(angle_map[name])))
    return ",".join(bits)


def aux_motors_status():
    angle_map = capture_aux_angles()
    return "MOTORS|" + format_aux_angle_list(angle_map)


# ============================================================
#  Programma-opslag: nieuw format + legacy fallback
# ============================================================

OP_WAYPOINT = 1
OP_WAIT = 2
OP_ALIGN = 3
OP_MOTOR_SNAPSHOT = 4
OP_MOTOR_TO_SNAPSHOT = 5
OP_RESET_ODO = 6
OP_STOP = 7


def build_record(opcode, payload=b""):
    payload = bytes(payload)
    if len(payload) > 255:
        raise ValueError("payload te groot")
    return bytes([opcode & 255, len(payload) & 255]) + payload


def parse_new_program(data):
    """
    Nieuw format:
      magic (2 bytes)
      records:
         opcode (1)
         payload_len (1)
         payload (n)
    """
    data = normalize_program_bytes(data)
    if data[0:2] != PROGRAM_MAGIC:
        return None

    out = []
    i = 2
    while i < len(data):
        if i + 2 > len(data):
            break
        opcode = data[i]
        payload_len = data[i + 1]
        if opcode == 0 and payload_len == 0:
            break
        start = i + 2
        end = start + payload_len
        if end > len(data):
            return None
        payload = bytes(data[start:end])
        out.append((opcode, payload))
        i = end
    return out


def parse_legacy_program(data):
    """
    Oude 8-byte record format uit je huidige code.
    Dit houdt bestaande slots zoveel mogelijk bruikbaar.
    """
    out = []
    data = normalize_program_bytes(data)

    for i in range(0, PROGRAM_BYTES, 8):
        if i + 7 >= len(data):
            break
        op = data[i]
        if op == 0:
            continue
        speed = data[i + 1]
        a = bytes_to_s16(data[i + 2], data[i + 3])
        b = bytes_to_s16(data[i + 4], data[i + 5])
        c = bytes_to_s16(data[i + 6], data[i + 7])

        if op == OP_WAYPOINT:
            out.append((OP_WAYPOINT, bytes([speed]) + bytes(s16_to_bytes(a)) + bytes(s16_to_bytes(b)) + bytes(s16_to_bytes(c if c != 0 else 15))))
        elif op == OP_WAIT:
            out.append((OP_WAIT, bytes(s16_to_bytes(a))))
        elif op == OP_ALIGN:
            out.append((OP_ALIGN, bytes([speed]) + bytes(s16_to_bytes(a)) + bytes([c & 255])))
        elif op == OP_MOTOR_SNAPSHOT:
            # Legacy snapshots kunnen we niet reconstructeren; we bewaren het als lege snapshot.
            out.append((OP_MOTOR_SNAPSHOT, b""))
        elif op == OP_MOTOR_TO_SNAPSHOT:
            out.append((OP_MOTOR_TO_SNAPSHOT, bytes([speed])))
        elif op == OP_RESET_ODO:
            out.append((OP_RESET_ODO, b""))
        elif op == OP_STOP:
            out.append((OP_STOP, b""))

    return out


def decode_program(data):
    new = parse_new_program(data)
    if new is not None:
        return [record_to_line(op, payload) for op, payload in new if record_to_line(op, payload)]
    legacy = parse_legacy_program(data)
    return [record_to_line(op, payload) for op, payload in legacy if record_to_line(op, payload)]


def line_to_record(line):
    """
    Ondersteunde programlijnen:
      WAYPOINT x y speed precision
      WAIT ms
      ALIGN yaw speed mode
      MOTOR_SNAPSHOT C:123 E:456
      MOTOR_TO_SNAPSHOT speed
      RESET_ODO
      STOP
    """
    parts = str(line).strip().split()
    if not parts:
        return None

    cmd = parts[0].upper()

    try:
        if cmd in ("WAYPOINT", "GOTO", "DRIVE_TO"):
            x_mm = int(parts[1])
            y_mm = int(parts[2])
            speed = int(parts[3]) if len(parts) > 3 else 150
            precision = int(parts[4]) if len(parts) > 4 else 15
            payload = bytes([clamp(speed, 0, 255)]) + bytes(s16_to_bytes(x_mm)) + bytes(s16_to_bytes(y_mm)) + bytes(s16_to_bytes(precision))
            return build_record(OP_WAYPOINT, payload)

        if cmd == "WAIT":
            ms = int(parts[1])
            payload = bytes(s16_to_bytes(ms))
            return build_record(OP_WAIT, payload)

        if cmd in ("ALIGN", "YAW"):
            yaw = int(parts[1])
            speed = int(parts[2]) if len(parts) > 2 else 120
            mode = int(parts[3]) if len(parts) > 3 else 0
            payload = bytes(s16_to_bytes(yaw)) + bytes([clamp(speed, 0, 255), clamp(mode, 0, 255)])
            return build_record(OP_ALIGN, payload)

        if cmd in ("MOTOR_SNAPSHOT", "SNAPSHOT"):
            payload = snapshot_line_to_payload(parts[1:])
            return build_record(OP_MOTOR_SNAPSHOT, payload)

        if cmd in ("MOTOR_TO_SNAPSHOT", "MOTORTOSNAPSHOT"):
            speed = int(parts[1]) if len(parts) > 1 else 150
            payload = bytes([clamp(speed, 0, 255)])
            return build_record(OP_MOTOR_TO_SNAPSHOT, payload)

        if cmd in ("RESET_ODO", "RESETODO"):
            return build_record(OP_RESET_ODO, b"")

        if cmd == "STOP":
            return build_record(OP_STOP, b"")
    except Exception:
        return None

    return None


def snapshot_line_to_payload(tokens):
    """
    tokens: ['C:123', 'Ei:45', ...]
    We slaan alleen niet-wiel motoren op.
    """
    items = []
    excluded = {wheel_left_port, wheel_right_port}

    for token in tokens:
        token = str(token).strip()
        if not token:
            continue

        # accommodeer zowel "C:123" als "C=123"
        if ":" in token:
            left, right = token.split(":", 1)
        elif "=" in token:
            left, right = token.split("=", 1)
        else:
            continue

        left = left.strip().upper()
        right = right.strip()
        try:
            angle = int(right)
        except:
            continue

        if left.endswith("I"):
            left = left[:-1]
        if left not in PORT_NAMES:
            continue
        if left in excluded:
            continue

        items.append((left, angle))

    payload = bytearray()
    payload.append(len(items) & 255)
    for name, angle in items:
        payload.append(port_index_from_name(name) & 255)
        payload.extend(bytes(s16_to_bytes(angle)))
    return bytes(payload)


def payload_to_snapshot_dict(payload):
    payload = bytes(payload)
    if not payload:
        return {}

    if len(payload) < 1:
        return {}

    count = payload[0]
    i = 1
    out = {}
    for _ in range(count):
        if i + 3 > len(payload):
            break
        port_idx = payload[i]
        angle = bytes_to_s16(payload[i + 1], payload[i + 2])
        i += 3
        name = port_name_from_index(port_idx)
        if name is None:
            continue
        if name == wheel_left_port or name == wheel_right_port:
            continue
        out[name] = angle
    return out


def record_to_line(op, payload):
    if op == OP_WAYPOINT:
        if len(payload) < 7:
            return None
        speed = payload[0]
        x_mm = bytes_to_s16(payload[1], payload[2])
        y_mm = bytes_to_s16(payload[3], payload[4])
        precision = bytes_to_s16(payload[5], payload[6])
        return "WAYPOINT {} {} {} {}".format(x_mm, y_mm, speed if speed else 150, precision if precision else 15)

    if op == OP_WAIT:
        if len(payload) < 2:
            return None
        ms = bytes_to_s16(payload[0], payload[1])
        return "WAIT {}".format(ms)

    if op == OP_ALIGN:
        if len(payload) < 4:
            return None
        yaw = bytes_to_s16(payload[0], payload[1])
        speed = payload[2]
        mode = payload[3]
        return "ALIGN {} {} {}".format(yaw, speed if speed else 120, mode)

    if op == OP_MOTOR_SNAPSHOT:
        snap = payload_to_snapshot_dict(payload)
        if not snap:
            return "MOTOR_SNAPSHOT"
        parts = []
        for name in sorted(snap.keys()):
            parts.append("{}:{}".format(name, int(snap[name])))
        return "MOTOR_SNAPSHOT " + " ".join(parts)

    if op == OP_MOTOR_TO_SNAPSHOT:
        speed = payload[0] if payload else 150
        return "MOTOR_TO_SNAPSHOT {}".format(speed)

    if op == OP_RESET_ODO:
        return "RESET_ODO"

    if op == OP_STOP:
        return "STOP"

    return None


def compile_lines(lines):
    data = bytearray()
    data.extend(PROGRAM_MAGIC)

    for line in lines:
        rec = line_to_record(line)
        if rec is None:
            continue
        if len(data) + len(rec) > PROGRAM_BYTES:
            return None
        data.extend(rec)

    if len(data) < PROGRAM_BYTES:
        data.extend(b"\x00" * (PROGRAM_BYTES - len(data)))

    return bytes(data[:PROGRAM_BYTES])


def load_slot(slot):
    if not slot_in_range(slot):
        return bytes([0] * PROGRAM_BYTES)
    return storage_read(program_offset(slot), PROGRAM_BYTES)


def save_slot(slot, data):
    if not slot_in_range(slot):
        print("ERR|SAVE|BAD_SLOT")
        return False

    data = normalize_program_bytes(data)
    ok = storage_write(program_offset(slot), data)
    if ok:
        slot_has_program[int(slot)] = any(b != 0 for b in data)
        print("OK|SAVE|" + str(int(slot)))
    return ok


def clear_slot(slot):
    if not slot_in_range(slot):
        return
    data = bytes([0] * PROGRAM_BYTES)
    save_slot(slot, data)
    slot_edit_buffer[int(slot)] = []
    slot_has_program[int(slot)] = False


def slot_used(slot):
    data = load_slot(slot)
    return any(b != 0 for b in data)


def refresh_slot_cache():
    for i in range(MAX_SLOTS):
        slot_has_program[i] = slot_used(i)


def list_slots():
    return "".join("1" if slot_has_program[i] else "0" for i in range(MAX_SLOTS))


# ============================================================
#  Snapshot-opslag / uitvoering
# ============================================================

def snapshot_baseline_reset(force_all=False):
    """
    Zet de referentie voor 'volgende snapshot' klaar.
    force_all=True betekent: de eerstvolgende snapshot moet alles opnemen.
    """
    global track_snapshot_baseline, track_snapshot_ready
    track_snapshot_baseline = capture_aux_angles()
    track_snapshot_ready = True
    if force_all:
        return True
    return True


def capture_snapshot_payload(force_all=False, threshold_deg=SNAPSHOT_THRESHOLD_DEG):
    """
    Leest motoren uit, vergelijkt met de vorige snapshot-baseline,
    en geeft payload terug in compact formaat:
      [count][port_idx][angle_hi][angle_lo]...
    """
    global track_snapshot_baseline, track_snapshot_ready

    current = capture_aux_angles()
    if not track_snapshot_ready:
        track_snapshot_baseline = dict(current)
        track_snapshot_ready = True

    items = []

    for name in sorted(current.keys()):
        if name == wheel_left_port or name == wheel_right_port:
            continue

        angle = int(current.get(name, 0))
        prev = int(track_snapshot_baseline.get(name, angle))

        if force_all or abs(angle - prev) >= int(threshold_deg):
            items.append((name, angle))

    # baseline bijwerken voor alle gemonitorde motoren
    for name in current.keys():
        track_snapshot_baseline[name] = int(current[name])

    payload = bytearray()
    payload.append(len(items) & 255)
    for name, angle in items:
        idx = port_index_from_name(name)
        if idx is None:
            continue
        payload.append(idx & 255)
        payload.extend(bytes(s16_to_bytes(angle)))

    return bytes(payload)


def append_snapshot_to_buffer(force_all=False):
    payload = capture_snapshot_payload(force_all=force_all)
    snap = payload_to_snapshot_dict(payload)
    if not snap:
        if force_all:
            # Geen aux motoren aangesloten. Niet fout; gewoon leeg.
            print("OK|MOTOR_SNAPSHOT|NONE")
            return True
        print("ERR|MOTOR_SNAPSHOT|EMPTY")
        beep("error")
        return False

    parts = []
    for name in sorted(snap.keys()):
        parts.append("{}:{}".format(name, int(snap[name])))
    line = "MOTOR_SNAPSHOT " + " ".join(parts)
    print(line)
    try:
        hub.display.on()
    except:
        pass
    wait(80)
    try:
        hub.display.off()
    except:
        pass
    beep("click")
    return line


def move_motor_to_target(motor_obj, target_angle, speed=150, timeout_ms=5000):
    """
    Robuust: probeer run_target; fallback naar track_target + polling.
    """
    target_angle = int(target_angle)
    speed = int(max(10, min(1000, speed)))

    # Probeer de nette variant eerst.
    try:
        motor_obj.run_target(speed, target_angle)
        return True
    except:
        pass

    # Fallback: drive-to-target tracking.
    try:
        motor_obj.track_target(target_angle)
    except:
        try:
            motor_obj.run_target(speed, target_angle)
            return True
        except Exception as e:
            print("ERR|MOTOR|TARGET|" + str(e))
            return False

    elapsed = 0
    while elapsed < timeout_ms:
        try:
            current = int(motor_obj.angle())
        except:
            return False
        if abs(current - target_angle) <= 2:
            return True
        service_runtime(max_messages=2)
        wait(20)
        elapsed += 20

    return True


def motor_to_snapshot(payload, speed=150):
    global aux_hold_blocked

    snap = payload_to_snapshot_dict(payload)
    if not snap:
        print("OK|MOTOR_SNAPSHOT|NONE")
        return True

    ok = True
    aux_hold_blocked = True
    try:
        for name in sorted(snap.keys()):
            if name == wheel_left_port or name == wheel_right_port:
                continue
            m = None
            for n, mo in aux_motors:
                if n == name:
                    m = mo
                    break
            if m is None:
                continue
            try:
                if not move_motor_to_target(m, snap[name], speed=speed):
                    ok = False
                    print("ERR|MOTOR_TO_SNAPSHOT|" + name)
            except Exception as e:
                ok = False
                print("ERR|MOTOR_TO_SNAPSHOT|" + name + "|" + str(e))
    finally:
        aux_hold_blocked = False
    return ok


# ============================================================
#  Rijlogica
# ============================================================

def check_hardware_stop():
    """
    Houdt de huidige 'druk CENTER om te stoppen' logica,
    maar alleen tijdens programma-uitvoering.
    """
    global stop_arm_armed, stop_requested
    buttons = safe_button_pressed()

    if not stop_arm_armed:
        if Button.CENTER not in buttons:
            stop_arm_armed = True
    elif Button.CENTER in buttons:
        stop_requested = True


def drive_to(target_x, target_y, max_speed=150, precision=15, timeout_ms=12000):
    global stop_requested, stop_arm_armed

    timeout = 0
    log_msg("Autonoom rijden naar: {}, {}".format(target_x, target_y))

    while timeout < timeout_ms:
        service_runtime()

        if stop_requested:
            robot.stop()
            log_msg("Programma gestopt")
            return False

        x_nu, y_nu, hoek_nu = update_odometrie()
        dx = target_x - x_nu
        dy = target_y - y_nu
        distance = sqrt(dx * dx + dy * dy)

        if distance < precision:
            robot.stop()
            return True

        doel_hoek = atan2(dy, dx) * 180 / pi
        fout = doel_hoek - hoek_nu

        while fout > 180:
            fout -= 360
        while fout < -180:
            fout += 360

        speed = min(max_speed, distance * 2.5)
        steering = fout * 3
        robot.drive(speed, steering)

        wait(20)
        timeout += 20

    robot.stop()
    return True


def align_yaw(target_yaw, speed=120, mode=0, timeout_ms=4000):
    global stop_requested

    timeout = 0
    speed = max(20, min(255, int(speed)))

    while timeout < timeout_ms:
        service_runtime()

        if stop_requested:
            robot.stop()
            return False

        _, _, current = update_odometrie()
        diff = target_yaw - current
        while diff > 180:
            diff -= 360
        while diff < -180:
            diff += 360

        if abs(diff) < 2:
            robot.stop()
            return True

        if int(mode) == 1:
            turn = abs(diff)
        elif int(mode) == 2:
            turn = -abs(diff)
        else:
            turn = max(-180, min(180, diff * 4))

        robot.drive(0, max(-speed, min(speed, int(turn))))
        wait(20)
        timeout += 20

    robot.stop()
    return True


def wait_ms(ms):
    global stop_requested
    elapsed = 0
    while elapsed < ms:
        service_runtime()
        if stop_requested:
            robot.stop()
            return False
        wait(20)
        elapsed += 20
    return True


def run_program(slot):
    global run_active, stop_requested, stop_arm_armed

    if run_active:
        print("ERR|RUN|BUSY")
        return False
    if tracking_mode:
        print("ERR|RUN|TRACKING")
        return False

    if not slot_in_range(slot):
        print("ERR|RUN|BAD_SLOT")
        return False

    data = load_slot(slot)
    program = decode_program(data)
    if not program:
        print("ERR|RUN|EMPTY")
        beep("error")
        return False

    run_active = True
    stop_requested = False
    stop_arm_armed = False
    
    reset_odometrie_naar_nul()
    beep("run")
    print("RUN|" + str(int(slot)))

    ok = True
    try:
        for line in program:
            if stop_requested:
                ok = False
                break

            service_runtime()

            parts = line.split()
            if not parts:
                continue

            cmd = parts[0].upper()

            try:
                if cmd == "WAYPOINT":
                    x_mm = int(parts[1])
                    y_mm = int(parts[2])
                    speed = int(parts[3]) if len(parts) > 3 else 150
                    precision = int(parts[4]) if len(parts) > 4 else 15
                    if not drive_to(x_mm, y_mm, speed, precision):
                        ok = False
                        break

                elif cmd == "WAIT":
                    if not wait_ms(int(parts[1])):
                        ok = False
                        break

                elif cmd == "ALIGN":
                    yaw = int(parts[1])
                    speed = int(parts[2]) if len(parts) > 2 else 120
                    mode = int(parts[3]) if len(parts) > 3 else 0
                    if not align_yaw(yaw, speed, mode):
                        ok = False
                        break

                elif cmd == "MOTOR_SNAPSHOT":
                    # Playback: ga naar de snapshot die in de lijn zit.
                    payload = snapshot_line_to_payload(parts[1:])
                    if not motor_to_snapshot(payload, speed=150):
                        ok = False

                elif cmd == "MOTOR_TO_SNAPSHOT":
                    # Compatibiliteit: zelfde gedrag als snapshot playback,
                    # maar als er geen payload is, gebruiken we niets.
                    payload = b""
                    if len(parts) > 1:
                        try:
                            sp = int(parts[1])
                        except:
                            sp = 150
                    else:
                        sp = 150
                    if not motor_to_snapshot(payload, speed=sp):
                        ok = False

                elif cmd == "RESET_ODO":
                    reset_odometrie_naar_nul()

                elif cmd == "STOP":
                    stop_requested = True
                    ok = False
                    break

            except Exception as e:
                print("ERR|RUN|" + str(e))
                ok = False
                break

    finally:
        robot.stop()
        run_active = False
        stop_requested = False
        stop_arm_armed = False

    if ok:
        beep("save")
        print("OK|RUN|DONE")
    else:
        beep("error")
        print("OK|RUN|STOPPED")
    return ok


# ============================================================
#  Tracking
# ============================================================

def start_tracking(slot=None):
    global tracking_mode, arm_mode, current_slot, buffer, stop_requested, aux_hold_blocked

    if slot is not None and slot_in_range(slot):
        current_slot = int(slot)

    if run_active:
        print("ERR|TRACK|BUSY")
        return False

    tracking_mode = True
    arm_mode = False
    stop_requested = False
    aux_hold_blocked = False
    buffer.clear()

    # Start van tracking = meteen een snapshot baseline én record in buffer.
    reset_odometrie_naar_nul()
    snapshot_baseline_reset(force_all=True)

    print("OK|TRACK|ON")
    beep("track")

    # Eerste snapshot opnemen in de buffer (full snapshot, dus alles vastleggen).
    buffer_line = append_snapshot_to_buffer(force_all=True)
    if buffer_line:
        track_buffer_append(buffer_line)

    send_pose()
    return True


def track_buffer_append(line):
    global buffer
    buffer.append(line)


def stop_tracking_and_save():
    global tracking_mode, arm_mode, slot_edit_buffer

    if not tracking_mode:
        return False

    data = compile_lines(buffer)
    if data is None:
        print("ERR|SAVE|NO_SPACE")
        beep("error")
        return False

    if not save_slot(current_slot, data):
        beep("error")
        return False

    slot_edit_buffer[current_slot] = list(buffer)
    slot_has_program[current_slot] = any(b != 0 for b in data)

    tracking_mode = False
    arm_mode = False
    buffer.clear()

    print("OK|TRACK|OFF")
    beep("save")
    return True


# ============================================================
#  Snapshot-taken tijdens tracking
# ============================================================

buffer = []


def take_tracking_snapshot():
    """
    LEFT tijdens tracking:
    - maak een snapshot
    - negeer wielen
    - laat motoren onder de threshold weg
    - sla op in de buffer
    """
    line = append_snapshot_to_buffer(force_all=False)
    if not line:
        return False
    track_buffer_append(line)
    return True


# ============================================================
#  Requests / antwoorden
# ============================================================

def send_version():
    print("VERSION|{}|{}".format(FIRMWARE_VERSION, PROTOCOL_VERSION))


def send_wheels():
    print("WHEELS|" + wheel_cfg_string())


def send_slots():
    print("SLOTS|" + list_slots())


def send_program(slot):
    if not slot_in_range(slot):
        print("ERR|PROGRAM|BAD_SLOT")
        return

    script = ";".join(decode_program(load_slot(slot)))
    print("SCRIPT|" + str(int(slot)) + "|" + script)


def send_programs_summary():
    occupied = []
    for i in range(MAX_SLOTS):
        if slot_has_program[i]:
            occupied.append(str(i))
    print("PROGRAMS|" + (",".join(occupied) if occupied else "none"))


def send_settings():
    print(
        "SETTINGS|wheels={}|slot={}|broadcast={}|program_bytes={}|max_slots={}|protocol={}".format(
            wheel_cfg_string(),
            current_slot,
            1 if auto_slot_broadcast else 0,
            PROGRAM_BYTES,
            MAX_SLOTS,
            PROTOCOL_VERSION,
        )
    )


def send_status():
    state = "TRACK" if tracking_mode else ("RUN" if run_active else "IDLE")
    print(
        "STATUS|{}|slot={}|tracking={}|run={}|arm={}|stop={}".format(
            state,
            current_slot,
            1 if tracking_mode else 0,
            1 if run_active else 0,
            1 if arm_mode else 0,
            1 if stop_requested else 0,
        )
    )


def send_all():
    print("OK|ALL")
    send_version()
    send_wheels()
    send_settings()
    send_slots()
    send_status()
    send_pose()
    send_programs_summary()
    print(aux_motors_status())


def send_ports():
    print("PORTS|" + ",".join(PORT_NAMES))


def send_aux():
    print(aux_motors_status())


def send_battery():
    # Niet elke hub/API-versie ondersteunt dit even netjes.
    try:
        voltage = hub.battery.voltage()
        current = hub.battery.current()
        print("BATTERY|{}|{}".format(voltage, current))
    except:
        print("BATTERY|UNKNOWN")


# ============================================================
#  Wheel configuratie wijzigen
# ============================================================

def apply_wheel_config(left_token, right_token):
    global wheel_left_port, wheel_left_inverted, wheel_right_port, wheel_right_inverted
    global current_slot

    left = parse_port_token(left_token)
    right = parse_port_token(right_token)

    if left is None or right is None:
        print("ERR|WHEELS|BAD_FORMAT")
        beep("error")
        return False

    left_name, left_inv = left
    right_name, right_inv = right

    if left_name == right_name:
        print("ERR|WHEELS|SAME_PORT")
        beep("error")
        return False

    if tracking_mode or run_active:
        print("ERR|WHEELS|BUSY")
        beep("error")
        return False

    wheel_left_port = left_name
    wheel_left_inverted = bool(left_inv)
    wheel_right_port = right_name
    wheel_right_inverted = bool(right_inv)

    try:
        build_drivebase()
        discover_aux_motors()
        save_settings()
        print("OK|WHEELS|" + wheel_cfg_string())
        send_slots()
        send_status()
        beep("click")
        return True
    except Exception as e:
        print("ERR|WHEELS|" + str(e))
        beep("error")
        return False


# ============================================================
#  Parser
# ============================================================

def verwerk_commando(raw):
    global current_slot, tracking_mode, arm_mode, stop_requested, manual_hold_requested

    line = str(raw).strip()
    if not line:
        return

    up = line.upper()

    try:
        if up == "PING":
            print("PONG")
            return

        if up == "LIST":
            send_slots()
            return

        if up.startswith("SEL|"):
            parts = line.split("|")
            try:
                current_slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
            except:
                current_slot = 0
            print("OK|SEL|" + str(current_slot))
            beep("click")
            return

        if up.startswith("LOAD|"):
            parts = line.split("|")
            try:
                slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
            except:
                slot = current_slot
            send_program(slot)
            return

        if up.startswith("CLR|") or up.startswith("CLEAR|"):
            parts = line.split("|")
            try:
                slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
            except:
                slot = current_slot
            clear_slot(slot)
            print("OK|CLR|" + str(slot))
            send_slots()
            beep("click")
            return

        if up.startswith("ADD|"):
            parts = line.split("|", 2)
            if len(parts) < 3:
                print("ERR|ADD|BAD_FORMAT")
                return
            try:
                slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
            except:
                slot = current_slot
            instruction = parts[2].strip()
            slot_edit_buffer[slot].append(instruction)
            print("OK|ADD|" + str(slot))
            return

        if up.startswith("END|") or up.startswith("SAVE|"):
            parts = line.split("|")
            try:
                slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
            except:
                slot = current_slot
            data = compile_lines(slot_edit_buffer[slot])
            if data is None:
                print("ERR|SAVE|NO_SPACE")
                beep("error")
                return
            save_slot(slot, data)
            slot_has_program[slot] = any(b != 0 for b in data)
            print("SCRIPT|" + str(slot) + "|" + ";".join(slot_edit_buffer[slot]))
            slot_edit_buffer[slot] = []
            send_slots()
            beep("save")
            return

        if up.startswith("RUNB|") or up.startswith("RUN|"):
            parts = line.split("|")
            try:
                slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
            except:
                slot = current_slot
            run_program(slot)
            return

        if up.startswith("REQUEST|"):
            req = line.split("|", 1)[1].strip().upper()
            handle_request(req)
            return

        if up.startswith("SET|WHEELS|"):
            parts = line.split("|", 2)
            if len(parts) < 3:
                print("ERR|WHEELS|BAD_FORMAT")
                return
            spec = parts[2].strip()
            if "," in spec:
                left, right = spec.split(",", 1)
            elif ";" in spec:
                left, right = spec.split(";", 1)
            else:
                print("ERR|WHEELS|BAD_FORMAT")
                beep("error")
                return
            apply_wheel_config(left.strip(), right.strip())
            return

        if up.startswith("WHEELS|"):
            # alias van SET|WHEELS|
            parts = line.split("|", 1)
            if len(parts) < 2:
                print("ERR|WHEELS|BAD_FORMAT")
                return
            spec = parts[1].strip()
            if "," in spec:
                left, right = spec.split(",", 1)
            elif ";" in spec:
                left, right = spec.split(";", 1)
            else:
                print("ERR|WHEELS|BAD_FORMAT")
                beep("error")
                return
            apply_wheel_config(left.strip(), right.strip())
            return

        if up == "TRACK|ON" or up == "TRACK|START":
            start_tracking(current_slot)
            return

        if up == "TRACK|OFF" or up == "TRACK|STOP":
            tracking_mode = False
            arm_mode = False
            buffer.clear()
            print("OK|TRACK|OFF")
            beep("click")
            return

        if up == "MOTORSNAPSHOT" or up == "MOTOR_SNAPSHOT":
            # Externe/handmatige call: maak snapshot van de huidige stand.
            append_snapshot_to_buffer(force_all=False)
            return

        if up.startswith("MOTORHOLD|"):
            # Bewust niet meer actief buiten RUN.
            manual_hold_requested = ("ON" in up)
            print("OK|MOTORHOLD|RUN_ONLY")
            return

        if up.startswith("DELETE|"):
            parts = line.split("|")
            try:
                slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
            except:
                slot = current_slot
            clear_slot(slot)
            print("OK|DELETE|" + str(slot))
            send_slots()
            return

        if up.startswith("STOP"):
            stop_requested = True
            try:
                robot.stop()
            except:
                pass
            print("OK|STOP")
            beep("error")
            return

        # oude / handige requests zonder REQUEST| prefix
        if up == "POS" or up == "REQPOS":
            send_pose()
            return

        if up == "SELECTED" or up == "CURRENT":
            print("SEL|" + str(current_slot))
            return

    except Exception as e:
        print("ERR|CMD|" + str(e))
        beep("error")


def handle_request(req):
    global current_slot

    if req == "SLOTS":
        send_slots()
        return

    if req == "WHEELS":
        send_wheels()
        return

    if req == "VERSION":
        send_version()
        return

    if req == "STATUS":
        send_status()
        return

    if req == "POSE":
        send_pose()
        return

    if req == "SETTINGS":
        send_settings()
        return

    if req == "PROGRAMS":
        send_programs_summary()
        return

    if req == "PROGRAMS_FULL":
        # handig voor debug, niet te groot gebruiken in production
        for i in range(MAX_SLOTS):
            if slot_has_program[i]:
                send_program(i)
        return

    if req.startswith("PROGRAM|"):
        parts = req.split("|")
        try:
            slot = max(0, min(MAX_SLOTS - 1, int(parts[1])))
        except:
            slot = current_slot
        send_program(slot)
        return

    if req == "ALL":
        send_all()
        return

    if req == "PORTS":
        send_ports()
        return

    if req == "AUX":
        send_aux()
        return

    if req == "BATTERY":
        send_battery()
        return

    if req == "SEL":
        print("SEL|" + str(current_slot))
        return

    if req == "FLASH":
        print("FLASH|program_bytes={}|settings_bytes={}|total={}".format(PROGRAM_BYTES, SETTINGS_BYTES, FLASH_TOTAL_BYTES))
        return

    print("ERR|REQ|UNKNOWN|" + req)
    beep("error")


# ============================================================
#  Display
# ============================================================

def update_led_matrix(tick):
    try:
        hub.display.off()
    except:
        pass

    if current_slot == ARM_SLOT:
        try:
            hub.display.pixel(4, 4, 100)
        except:
            pass
        return

    col = current_slot // 5
    row = current_slot % 5

    if tracking_mode:
        if tick % 2 == 0:
            try:
                hub.display.pixel(col, row, 100)
            except:
                pass
    elif arm_mode:
        if tick % 6 < 3:
            try:
                hub.display.pixel(col, row, 100)
            except:
                pass
        try:
            hub.display.pixel(4, 4, 30)
        except:
            pass
    elif run_active:
        if tick % 3 == 0:
            try:
                hub.display.pixel(col, row, 100)
            except:
                pass
    else:
        try:
            hub.display.pixel(col, row, 100)
        except:
            pass


# ============================================================
#  Boot / init
# ============================================================

def initialize():
    global last_distance

    load_settings()
    build_drivebase()
    discover_aux_motors()
    refresh_slot_cache()

    reset_odometrie_naar_nul()
    try:
        dist, _, _, _ = robot.state()
        last_distance = dist
    except:
        last_distance = 0.0


def boot_banner():
    print("========================================")
    print("  FLASH-POWERED ROBOTRACK SYSTEM READY  ")
    print("========================================")
    send_version()
    send_wheels()
    send_settings()
    send_slots()
    send_status()
    send_ports()
    send_pose()
    send_aux()
    print("READY")
    beep("startup")


# ============================================================
#  Hoofdloop
# ============================================================

def run_main_loop():
    global last_slot_broadcast_ms, current_slot, tracking_mode, arm_mode
    last_buttons = set()
    display_tick = 0
    loop_tick = 0

    while True:
        read_all_pending(max_messages=8)

        buttons = safe_button_pressed()
        pressed_now = buttons - last_buttons
        last_buttons = buttons

        # Live pose blijft beschikbaar voor debug / webapp.
        if tracking_mode or (loop_tick % 4 == 0 and not run_active):
            try:
                x_live, y_live, hoek_live = update_odometrie()
                print("DATA:{},{},{}".format(int(x_live), int(y_live), int(hoek_live)))
            except:
                pass

        if tracking_mode:
            if Button.RIGHT in pressed_now:
                line = "WAYPOINT {} {} {} {}".format(int(x_pos), int(y_pos), 150, 15)
                track_buffer_append(line)
                print(line)
                beep("click")

            if Button.LEFT in pressed_now:
                take_tracking_snapshot()

            if Button.CENTER in pressed_now:
                stop_tracking_and_save()

        elif arm_mode:
            if Button.LEFT in pressed_now:
                current_slot = (current_slot - 1) % MAX_SLOTS
                beep("click")
            if Button.RIGHT in pressed_now:
                current_slot = (current_slot + 1) % MAX_SLOTS
                beep("click")
            if Button.CENTER in pressed_now:
                log_msg("Start tracking voor slot " + str(current_slot))
                start_tracking(current_slot)

        else:
            if Button.LEFT in pressed_now:
                if current_slot == 0:
                    current_slot = ARM_SLOT
                elif current_slot == ARM_SLOT:
                    current_slot = MAX_SLOTS - 1
                else:
                    current_slot -= 1
                beep("click")

            if Button.RIGHT in pressed_now:
                if current_slot == MAX_SLOTS - 1:
                    current_slot = ARM_SLOT
                elif current_slot == ARM_SLOT:
                    current_slot = 0
                else:
                    current_slot += 1
                beep("click")

            if Button.CENTER in pressed_now:
                if current_slot == ARM_SLOT:
                    arm_mode = True
                    current_slot = 0
                    print("OK|ARM")
                    beep("click")
                else:
                    run_program(current_slot)

        update_led_matrix(display_tick)

        display_tick = (display_tick + 1) % 60
        loop_tick += 1

        # Optionele slot broadcast uitzetten/aanzetten via settings.
        if auto_slot_broadcast:
            # simpele loop-timer-benadering: ongeveer elke 200 ms
            if loop_tick % 4 == 0:
                send_slots()

        wait(50)


# ============================================================
#  Start
# ============================================================

initialize()
boot_banner()
run_main_loop()

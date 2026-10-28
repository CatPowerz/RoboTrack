
import sys

from pybricks.hubs import PrimeHub
from pybricks.pupdevices import Motor, ColorSensor, UltrasonicSensor, ForceSensor
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch
from umath import sin, cos, atan2, sqrt, pi
from usys import stdin
from uselect import poll
from pybricks.parameters import Axis
import ustruct
hub = PrimeHub()

hub.display.orientation(Side.LEFT)
hub.system.set_stop_button(None)
timer = StopWatch()
poller = poll()
poller.register(stdin)
leftmotorport = Port.F
rightmotorport = Port.B
dirleftwheel = Direction.COUNTERCLOCKWISE
dirrightwheel = Direction.CLOCKWISE
leftmotor = Motor(leftmotorport, dirleftwheel)
rightmotor = Motor(rightmotorport, dirrightwheel)
# Please edit direction config if you're not using the same direction as me
tick = 0
wheeldiameter = 81.6
axle = 140 # distance between left and right wheel
last_buttons = set()
bytesperprogram = 640 # standard config for custom 8 kb robotrack pybricks firmware.
maxprograms = 12

stoprequested = False
# ADAPTIVE recovery configuration. Values are in mm, degrees and milliseconds.
position_tolerance = 10
recovery_limit = 5000
progress_window = 650
progress_distance = 5
recovery_backoff = 35
mission_limit = 150000
motionclock = StopWatch()
mission_start = None
last_waypoint = (0.0, 0.0)
slotmask_dirty = True
slotmask_cache = 0

robot = DriveBase(leftmotor, rightmotor, wheeldiameter, axle)
robot.settings(straight_speed=500, straight_acceleration=800, turn_rate=350, turn_acceleration=2000)

global aux_motors, aux_last_angles
aux_motors = []
aux_last_angles = {}

tracking = False
whattracking = 0
editmode = True
selectedslot = 0

excluded = {"F", "B"}
for name in ["A", "B", "C", "D", "E", "F"]:
    if name in excluded:
        continue
    port = getattr(Port, name, None)
    if port is None:
        continue
    try:
        m = Motor(port)
        aux_motors.append((name, m))
        m.stop() # Let the user move the attachment by hand when recording.
        try:
            aux_last_angles[name] = int(m.angle())
        except:
            aux_last_angles[name] = 0
    except:
        pass

def updatelastangles():
    for name, m in aux_motors:
        if name is None:
            continue
        try:
            aux_last_angles[name] = int(m.angle())
        except:
            aux_last_angles[name] = 0


editmode = False

tracking = False
running = False

x = 0.0
y = 0.0

# signed 16-bit (-32768 to 32767)
def s16_to_bytes(v):
    return ustruct.pack(">h", int(max(-32768, min(32767, v))))

def bytes_to_s16(hi, lo):
    return ustruct.unpack(">h", bytes([hi, lo]))[0]

# unsigned 16-bit (0 to 65535)
def u16_to_bytes(v):
    return ustruct.pack(">H", int(max(0, min(65535, v))))

def bytes_to_u16(hi, lo):
    return ustruct.unpack(">H", bytes([hi, lo]))[0]

last_distance = 0.0
last_heading = 0.0

def normalize_angle(angle):
    return (angle + 180) % 360 - 180

def update_odometry():
    global x, y, last_distance, last_heading
    distance = robot.distance()
    difference = distance - last_distance
    angle = hub.imu.heading()

    # spicy formulas (midpoint heading reduces errors during curved driving)
    middle_angle = last_heading + normalize_angle(angle - last_heading) / 2
    rad = -middle_angle * pi / 180

    x += difference * cos(rad)
    y += difference * sin(rad)

    # so basically because you know the robot heading and the distance he travelled you can know where it went
    last_distance = distance
    last_heading = angle
    return x, y, angle

def reset_odometry():
    global x, y, last_distance, last_heading, last_waypoint
    x = 0.0
    y = 0.0
    robot.stop()
    robot.reset()
    hub.imu.reset_heading(0)
    wait(10)
    last_distance = robot.distance()
    leftmotor.reset_angle(0)
    rightmotor.reset_angle(0)
    
    for name, m in aux_motors:
        try:
            m.stop()
            m.reset_angle(0)
        except:
            pass

    updatelastangles()
    wait(10)
    last_distance = robot.distance()
    last_heading = hub.imu.heading()
    last_waypoint = (0.0, 0.0)

def writeflash(start, data):
    global slotmask_dirty
    start = int(start)
    if start < 0 or start + len(data) > maxprograms * bytesperprogram:
        print("Flash Writing Error: invalid address")
        return False
    try:
        hub.system.storage(start, write = bytes(data))
        if hub.system.storage(start, read=len(data)) != bytes(data):
            print("Flash Writing Error: verification failed")
            return False
        slotmask_dirty = True
        return True
    except:
        print ("Flash Writing Error")
        return False

def readflash(start, amount):
    try:
        data = hub.system.storage(int(start), read=int(amount))
        
        if len(data) < amount:
            data = data + bytes([0] * (amount - len(data)))
        return bytes(data[:amount])
    except:
        return bytes([0] * int(amount))

def saveslot(slot, data):
    if not valid_slot(slot) or len(data) > bytesperprogram:
        print("Error: invalid slot or size")
        return False
    slotoffset = int(slot) * bytesperprogram
    return writeflash(slotoffset, data)

def loadslot(slot):
    if not valid_slot(slot):
        print("Error: invalid slot")
        return bytes([0] * bytesperprogram)
    slotoffset = int(slot) * bytesperprogram
    try:
        returneddata = readflash(slotoffset, bytesperprogram)
        if len(returneddata) < bytesperprogram:
            returneddata = returneddata + bytes([0]*(bytesperprogram - len(returneddata)))
        return returneddata
    except Exception as error:
        print("Error reading slot OR empty: " + str(error))
        return bytes([0] * bytesperprogram)
    
def peekinline():
    data = poller.poll(0)
    if data:
        foundline = stdin.readline()
        return str(foundline.strip())
    else:
        return None

def valid_slot(slot):
    try:
        return 0 <= int(slot) < maxprograms
    except (ValueError, TypeError):
        return False

def release_aux_motors():
    for name, m in aux_motors:
        try:
            m.stop()  # Freewheel, not HOLD; manual snapshots remain possible.
        except:
            pass

def processcommand(data):

    global tracking, selectedslot, editmode, running, stoprequested

    data = data.upper()
    parts = data.split("|", 1)
    parameter = ""
    print("command: ", data)
    if len(parts) <= 1:
        command = data
    else:
        command = parts[0].strip()
        parameter = parts[1].strip()
    if command == "GETPOS":
        update_odometry()
        print("RequestPos:"+ str(x) + "|" + str(y) + "|" + str(hub.imu.heading()))
    if command == "CLEAR":
        slot = parameter
        if not running and clearslot(slot):
            print(f"SLOT_CLEARED:{parameter}")
   
    if command == "GETSLOT" and valid_slot(parameter):
        print(readflash(int(parameter) * bytesperprogram, bytesperprogram))
    if command == "STARTTRACKING" and not running and valid_slot(parameter):
        tracking = True
        selectedslot = int(parameter)
        release_aux_motors()
    if command == "SHUTDOWN":
        hub.system.shutdown()
    if command == "STOP":
        running = False
        robot.stop()
        release_aux_motors()
        stoprequested = True
        tracking = False
        editmode = False


def service_motion():
    global stoprequested
    if Button.CENTER in hub.buttons.pressed() or stoprequested:
        stoprequested = True
        robot.stop()
        release_aux_motors()
        return False
    if mission_start is not None and motionclock.time() - mission_start >= mission_limit:
        print("ROBOTRACK: mission time limit")
        stoprequested = True
        robot.stop()
        release_aux_motors()
        return False
    line = peekinline()
    if line is not None:
        processcommand(line)
    if stoprequested:
        robot.stop()
        return False
    return True

def backoff(direction, deadline):
    # Move away from the obstacle, opposite to the direction we were driving.
    robot.stop()
    update_odometry()
    initial = robot.distance()
    start = motionclock.time()
    robot.drive(-direction * 110, 0)
    while abs(robot.distance() - initial) < recovery_backoff:
        if motionclock.time() >= deadline or motionclock.time() - start >= 500:
            break
        if not service_motion():
            robot.stop()
            return False
        wait(20)
    robot.stop()
    update_odometry()
    return not stoprequested and motionclock.time() < deadline

def drive_to(tx, ty, speed, precision, specificdir, deadline=None, allow_recovery=True):
    global stoprequested, last_waypoint
    # 0 = automatic; 1 = forward; 2 = reverse. Old waypoints store 0.
    direction_mode = specificdir
    if speed == '' or speed == 0:
        speed = 150
    if speed < 0:
        speed = -speed
        direction_mode = 2
    speed = max(35, min(500, int(speed)))
    precision = position_tolerance # fixed position tolerance; flag2 remains stored unchanged
    update_odometry()
    distance = sqrt((tx-x)**2 + (ty-y)**2)
    if distance <= precision:
        last_waypoint = (tx, ty)
        return True

    heading_target = -atan2(ty-y, tx-x) * 180 / pi
    heading_error = normalize_angle(heading_target - hub.imu.heading())
    direction = -1 if direction_mode == 2 or (direction_mode != 1 and abs(heading_error) > 90) else 1
    desired_heading = heading_target if direction == 1 else heading_target + 180
    if not turnto(desired_heading, min(200, max(90, speed)), 4, '', deadline):
        if stoprequested or not allow_recovery:
            return False
        turn_recovery_deadline = motionclock.time() + recovery_limit
        if not backoff(direction, turn_recovery_deadline):
            return False
        if not turnto(desired_heading, min(180, speed), 5, '', turn_recovery_deadline):
            return False

    # A waypoint is allowed enough time for its distance/speed, not an infinite loop.
    started = motionclock.time()
    limit = max(2500, int(distance * 4000 / speed) + 2000)
    limit = min(30000, limit)
    if deadline is not None:
        limit = min(limit, max(0, deadline - started))
    progress_time = started
    progress_distance = distance
    previous_waypoint = last_waypoint
    retries = 0
    tilted_since = None
    recovery_deadline = None
    reorientations = 0
    while True:
        if not service_motion():
            robot.stop()
            return False
        update_odometry()
        dx = tx-x
        dy = ty-y
        distance = sqrt(dx**2 + dy**2)
        if distance <= precision:
            robot.stop()
            last_waypoint = (tx, ty)
            return True
        now = motionclock.time()
        if recovery_deadline is not None and now >= recovery_deadline:
            robot.stop()
            print("ROBOTRACK: recovery time exhausted")
            return False
        if now - started > limit or (deadline is not None and now >= deadline):
            robot.stop()
            print("ROBOTRACK: waypoint timeout")
            return False

        target_heading = -atan2(dy, dx) * 180 / pi
        if direction == -1:
            target_heading += 180
        err = normalize_angle(target_heading - hub.imu.heading())
        # When the target ends up behind us, steering harder causes endless
        # forward/backward corrections. Stop and realign once instead.
        if abs(err) > 85:
            robot.stop()
            if reorientations >= 1:
                print("ROBOTRACK: heading unstable")
                return False
            reorientations += 1
            turn_deadline = started + limit
            if deadline is not None:
                turn_deadline = min(turn_deadline, deadline)
            if recovery_deadline is not None:
                turn_deadline = min(turn_deadline, recovery_deadline)
            if not turnto(target_heading, min(180, speed), 5, '', turn_deadline):
                return False
            progress_time = motionclock.time()
            progress_distance = distance
            continue
        turn_rate = max(-90, min(90, err * 1.8))
        # Keep waypoint speed adjustable; slow near the target and sharp bends.
        current_speed = min(speed, max(35, distance * 2.5))
        if abs(err) > 45:
             current_speed = min(current_speed, 70)
        # Obstacles can pitch/roll the robot; be permissive, but slow down.
        try:
            tilt = hub.imu.tilt()
            maximum_tilt = max(abs(tilt[0]), abs(tilt[1]))
            if maximum_tilt > 18:
                current_speed = min(current_speed, 85)
            if maximum_tilt > 45:
                if tilted_since is None:
                    tilted_since = now
                elif now - tilted_since > 500:
                    robot.stop()
                    print("ROBOTRACK: robot tipped; position uncertain")
                    return False
            else:
                tilted_since = None
        except:
            pass
        robot.drive(current_speed * direction, turn_rate)

        if distance < progress_distance - distance:
            progress_distance = distance
            progress_time = now
            # Keep the same recovery deadline: temporary progress must not
            # restart the 5-second budget after another stall.
        if now - progress_time >= progress_window and distance > precision + 18:
            robot.stop()
            if not allow_recovery:
                print("ROBOTRACK: waypoint blocked")
                return False
            if recovery_deadline is None:
                recovery_deadline = now + recovery_limit
            if retries >= 2:
                # Try the last reliable waypoint, then one final attempt.
                # The same 5-second budget applies; never blindly reset (0,0).
                if recovery_deadline is not None and now < recovery_deadline:
                    px, py = previous_waypoint
                    if sqrt((px-x)**2 + (py-y)**2) > precision:
                        if drive_to(px, py, min(140, speed), precision, 0, recovery_deadline, False):
                            return drive_to(tx, ty, speed, precision, specificdir, recovery_deadline, False)
                print("ROBOTRACK: waypoint blocked after recovery")
                return False
            if recovery_deadline is None:
                recovery_deadline = now + recovery_limit
            retries += 1
            if now >= recovery_deadline or not backoff(direction, recovery_deadline):
                print("ROBOTRACK: recovery expired")
                return False
            # Reorient to the same target. Do not silently change drive direction.
            update_odometry()
            heading_target = -atan2(ty-y, tx-x) * 180 / pi
            desired_heading = heading_target if direction == 1 else heading_target + 180
            if not turnto(desired_heading, min(180, speed), 5, '', recovery_deadline):
                return False
            now = motionclock.time()
            progress_time = now
            progress_distance = sqrt((tx-x)**2 + (ty-y)**2)
            # Do NOT reset started or limit. The waypoint has one absolute
            # timeout even if repeated recovery attempts make small progress.
        wait(20)

def get_robot_heading():
    h = (hub.imu.heading() + 90) % 360
    return h - 360 if h > 180 else h
def get_occupied_mask():
    global slotmask_cache, slotmask_dirty
    if not slotmask_dirty:
        return slotmask_cache
    mask = 0
    for s in range(maxprograms):
        data = readflash(s * bytesperprogram, 1)
        if data and data[0] != 0:
            mask |= (1 << (s + 1))
    slotmask_cache = mask
    slotmask_dirty = False
    return mask

def turnto(angle, speed, precision, specificdir, deadline=None):
    global stoprequested
    update_odometry()
    speed = 180 if speed <= 0 else max(35, min(350, abs(int(speed))))
    precision = 3 if precision <= 0 else precision
    err = normalize_angle(angle - hub.imu.heading())
    if abs(err) <= precision:
        return True
    direction = 0
    if specificdir == 'R' or specificdir == 1:
        direction = 1
    elif specificdir == 'L' or specificdir == 2:
        direction = -1
    if direction == 1 and err < 0:
        err += 360
    elif direction == -1 and err > 0:
        err -= 360
    started = motionclock.time()
    limit = max(1600, int(abs(err) * 3500 / speed) + 1000)
    last_progress = started
    last_heading_seen = hub.imu.heading()
    while True:
        if not service_motion():
            robot.stop()
            return False
        update_odometry()
        heading = hub.imu.heading()
        short_err = normalize_angle(angle - heading)
        if abs(short_err) <= precision:
            robot.stop()
            return True
        err = short_err
        if direction == 1 and err < 0:
            err += 360
        elif direction == -1 and err > 0:
            err -= 360
        now = motionclock.time()
        if now - started > limit or (deadline is not None and now >= deadline):
            robot.stop()
            print("ROBOTRACK: turn timeout")
            return False
        if abs(normalize_angle(heading - last_heading_seen)) > 1.5:
            last_progress = now
            last_heading_seen = heading
        if now - last_progress > 650:
            robot.stop()
            print("ROBOTRACK: turn blocked")
            return False
        turnrate = max(-speed, min(speed, err * 4.0))
        minimum = min(55, max(30, abs(short_err) * 5))
        if abs(turnrate) < minimum:
            turnrate = minimum if err > 0 else -minimum
        robot.drive(0, turnrate)
        wait(20)

def clearslot(slot):
    if not valid_slot(slot):
        return False
    slotoffset = int(slot) * bytesperprogram
    return writeflash(slotoffset, bytes([0] * bytesperprogram))

def updateinterface():
    global timer
    blink_on = (timer.time() % 200) < 100
    if tracking:
        
        if(blink_on):
            hub.display.pixel(selectedslot // 5, selectedslot % 5, brightness=100)
        else:
            hub.display.off()
       
        
    elif editmode:
        hub.display.off()
        hub.display.pixel(selectedslot // 5, selectedslot % 5, brightness=100)
        if selectedslot == 24:
            hub.display.pixel(4, 4, brightness=75)
        else:
            hub.display.pixel(4, 4, brightness=50)
    else:
        hub.display.off()
        hub.display.pixel(selectedslot // 5, selectedslot % 5, brightness=100)

def selectslot():
    global tracking, editmode, selectedslot, running
    if tracking:
        tracking = False
    elif editmode:
        if selectedslot == 24:
            editmode = False
        else:
            if not clearslot(selectedslot):
                return
            reset_odometry()
            release_aux_motors()
            tracking = True
            updatelastangles()
            editmode = False
    else:
        if selectedslot == 24:
            editmode = True
            selectedslot = 0
        else:
            if not editmode:
                running = True
                runprogram(selectedslot)


def runprogram(slot):
    global bytesperprogram, selectedslot, stoprequested, running, tracking, editmode, mission_start
    while Button.CENTER in hub.buttons.pressed():
        wait(20)
    if not valid_slot(slot):
        return False
    reset_odometry()
    stoprequested = False
    running = True
    mission_start = motionclock.time()
    # EVERY instruction has 8 bytes. Every bite consists of eight bits (0 or 1)
    # The first byte contains the type of instruction (from 0 to 255)
    # A byte is SIGNED if it can also contain negative numbers, UNSIGNED if only positive
    # Byte 2 and 3 is parameter 1, byte 4 and 5 parameter 2, byte 6, 7 and 8 are 'flags'.
    # Flags are for small extras like reverse or not.
    data = loadslot(slot)
    succeeded = True
    for i in range(0, bytesperprogram // 8):
        if not service_motion():
            succeeded = False
            break
        curroffset = 8 * i
        cmd, p1, p2, flag1, flag2, flag3 = ustruct.unpack(">BhhBBB", data[curroffset : curroffset + 8])
        if cmd == 0:
            break
        try:
            if cmd == 1:
                # flag3 was unused for driving; older recordings have value 0.
                succeeded = drive_to(p1, p2, flag1, flag2, flag3)
            elif cmd == 2:
                succeeded = turnto(p1, flag1, flag2, flag3)
            elif cmd == 3:
                succeeded = playmotorsnapshot(p1, p2, flag1, flag2, flag3)
            else:
                print("ROBOTRACK: unknown instruction", cmd)
                succeeded = False
        except Exception as error:
            print("ROBOTRACK: instruction error", error)
            succeeded = False
        if not succeeded:
            break
    robot.stop()
    release_aux_motors()
    print("program finished")
    tracking = False
    running = False
    editmode = False
    mission_start = None
    stoprequested = False
    return succeeded

def saveinstruction(slot, cmd, p1, p2, flag1, flag2, flag3):
    if not valid_slot(slot):
        return False
    offset = countinstructions(slot)
    if offset >= bytesperprogram // 8:
        print("ROBOTRACK: slot full")
        return False
    totaloffset = (offset * 8) + (bytesperprogram * int(slot))
    try:
        data = ustruct.pack(">BhhBBB", cmd, p1, p2, flag1, flag2, flag3)
    except (ValueError, OverflowError):
        return False
    return writeflash(totaloffset, data)

def countinstructions(slot):
    if not valid_slot(slot):
        return bytesperprogram // 8
    data = loadslot(slot)
    count = 0
    for offset in range(0, bytesperprogram, 8):
        cmd = data[offset]  # Byte 0 is the type
        if cmd == 0:
            break
        count += 1
    return count
def playmotorsnapshot(p1, p2, flag1, flag2, flag3):
    # p1/p2 follow the set bits in mask, not the indices of connected motors.
    # This also decodes old recordings with only one motor moved.
    targets = []
    for idx, (name, m) in enumerate(aux_motors):
        if flag1 & (1 << idx):
            targets.append((m, p1 if len(targets) == 0 else p2))
    if len(targets) > 2:
        print("ROBOTRACK: snapshot requires more than two motors")
        return False
    maximum_rotation = 0
    for m, target in targets:
        maximum_rotation = max(maximum_rotation, abs(target - m.angle()))
        try:
            m.run_target(max(1, flag2), target, then=Stop.COAST, wait=False)
        except Exception as error:
            print("Error with playmotorsnapshot", error)
            release_aux_motors()
            return False
    if flag3:
        started = motionclock.time()
        allowed_time = max(2500, min(12000, int(maximum_rotation * 3000 / max(1, flag2)) + 1000))
        while True:
            if not service_motion():
                release_aux_motors()
                return False
            try:
                if all(m.done() for m, _ in targets):
                    break
            except Exception as error:
                print("ROBOTRACK: motor feedback error", error)
                release_aux_motors()
                return False
            if motionclock.time() - started > allowed_time:
                print("ROBOTRACK: motor snapshot timeout")
                release_aux_motors()
                return False
            wait(20)
        release_aux_motors()
    return True

def motorsnapshot(speed, waitformotors):
    
    global aux_last_angles
    editedmotors = []
    mask = 0
    for idx, (name, m) in enumerate(aux_motors):
        if name is None:
            continue
        try:
            currangle = m.angle()
            delta = int(currangle - aux_last_angles.get(name, 0))
            if m.angle() - aux_last_angles[name] > 5 or m.angle() - aux_last_angles[name] < -5:
              
                mask |= (1 << idx)
                editedmotors.append(currangle)
                print("Motor ", name, "CurrentAngle ", currangle, "Last ", aux_last_angles[name], "Difference ", delta)
            else:
                print("Motor ", name, "CurrentAngle ", currangle, "Last ", aux_last_angles[name], "Difference ", delta)
                print("motor " + name + " has not moved more than 5 deg")
             
        except:
            print("Error with motorsnapshot")
    if len(editedmotors) == 0:
        return None
    if len(editedmotors) > 2:
        print("ROBOTRACK: max two changed motors per snapshot")
        return None

    p1 = editedmotors[0]
    if len(editedmotors) >= 2:
        
        p2 = editedmotors[1]
    else:
        p2 = 0
    flag1 = mask
    flag2 = speed
    flag3 = waitformotors
    updatelastangles()
    return ustruct.pack(">BhhBBB", 3, p1, p2, flag1, flag2, flag3)

while True:

    buttons = hub.buttons.pressed()
    pressed_now = [but for but in buttons if but not in last_buttons]
    last_buttons = buttons
    
    tick += 1
    if tracking or tick == 3:
        
        rawcapacity = hub.battery.voltage()

        capacity = max(0.0, min(100.0, (rawcapacity - 7000) / 12))
        tick = 0
        robot_pitch = hub.imu.tilt()[1]
        robot_roll = -hub.imu.tilt()[0]
        robot_heading = hub.imu.heading()

        mask = get_occupied_mask()
        data = f"{x},{y},{robot_heading},{robot_pitch},{robot_roll},{capacity},{mask}\n"
        print(data)

         
          
    update_odometry()
    updateinterface()
   
   
    newdata = peekinline()
    if newdata != None: 

        processcommand(newdata)
    
    if Button.CENTER in pressed_now:
        if tracking:
            release_aux_motors()
            reset_odometry()
            tracking = False
            editmode = False
        elif running:
            running = False
            robot.stop()
            release_aux_motors()

            stoprequested = True
            tracking = False
            editmode = False
        else:
            selectslot()
        

    if Button.RIGHT in pressed_now:
        if tracking:

            saveinstruction(selectedslot, 1, int(x), int(y), 250, position_tolerance, 0)
            
        else:
            if selectedslot == 24:
                selectedslot = 0
            elif selectedslot >= maxprograms - 1:
                selectedslot = 24
            else:
                selectedslot = selectedslot + 1
        
        

    if Button.LEFT in pressed_now:
        if tracking:
            shot = motorsnapshot(255, 1)
            if shot is not None:
                if countinstructions(selectedslot) >= bytesperprogram // 8:
                    print("ROBOTRACK: slot full")
                else:
                    totaloffset = (countinstructions(selectedslot) * 8) + (bytesperprogram * selectedslot)
                    if writeflash(totaloffset, shot):
                        updatelastangles()
        else:
            if selectedslot <= 0:
                selectedslot = 24
            elif selectedslot == 24:
                selectedslot = maxprograms - 1
            else:
                selectedslot = selectedslot - 1    
    if Button.BLUETOOTH in pressed_now:
            if tracking:
                print(" ")
                
            else:
                if selectedslot <= 0:
                    selectedslot = 24
                elif selectedslot == 24:
                    selectedslot = maxprograms - 1
                else:
                    selectedslot = selectedslot - 1    
    

    wait(20)

    



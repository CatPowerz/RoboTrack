
from pybricks.hubs import PrimeHub
from pybricks.pupdevices import Motor, ColorSensor, UltrasonicSensor, ForceSensor
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch
from umath import sin, cos, atan2, sqrt, pi
from usys import stdin
from uselect import poll
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


robot = DriveBase(leftmotor, rightmotor, wheeldiameter, axle)
robot.settings(straight_speed=500, straight_acceleration=800, turn_rate=300, turn_acceleration=600)

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

def update_odometry():
    global x, y, last_distance
    distance = robot.distance()
    difference = distance - last_distance

    angle = hub.imu.heading()

    # spicy formulas

    rad = -angle * pi / 180

    x += difference * cos(rad)
    y += difference * sin(rad)

    # so basically because you know the robot heading and the distance he travelled you can know where it went
    last_distance = distance
    return x, y, angle

def reset_odometry():
    global x, y, last_distance
    x = 0.0
    y = 0.0
    hub.imu.reset_heading(0)
    robot.reset()
    wait(10)
    last_distance = robot.distance()
    

def writeflash(start, data):
    try:
        hub.system.storage(int(start), write = bytes(data))
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
    slotoffset = slot * bytesperprogram
    if slotoffset + len(data) > 8096:
        print("Error: 8 kb exceeded")
        return False
    else:
        writeflash(slotoffset, data)

def loadslot(slot):
    slotoffset = slot * bytesperprogram
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




def processcommand(data):
    data = data.upper()
    parts = data.split("|", 1)
    parameter = ""
    if len(parts) <= 1:
        command = data
    else:
        command = parts[0].strip()
        parameter = parts[1].strip()

   
    if command == "GETPOS":
        update_odometry()
        print("RequestPos:"+ str(x) + "|" + str(y) + "|" + str(hub.imu.heading()))
    if command == "GETSLOT":
        
        print(readflash(int(parameter) * bytesperprogram, bytesperprogram))
    #add more when there comes

def drive_to(tx, ty, speed, precision):
    if speed == '' or speed < 100:
        speed = 150
        

    update_odometry()
    differencex = tx-x
    differencey = ty-y
    distance=sqrt(differencex**2 + differencey**2)
    tangle = -atan2(differencey, differencex) * 180 / pi
    turnto(tangle, 100, precision, '')
    
    while distance > precision:
        update_odometry()
        differencex = tx-x
        differencey = ty-y
        distance=sqrt(differencex**2 + differencey**2)
        
        tangle = -atan2(differencey, differencex) * 180 / pi
        err = tangle - hub.imu.heading()
        if err > 180:
            err -= 360
        if err < -180:
            err += 360
        if speed < 0:
            err = -err
        if distance < precision * 2:
            err = 0
        turn_rate = max(-60, min(60, err * 1.0))
      #  current_speed = min(speed, max(90, distance * 2.5))
        robot.drive(speed, turn_rate)
        wait(10)


    robot.stop()
    wait(100)

def turnto(angle, speed, precision, specificdir):
    update_odometry()
    err = angle - hub.imu.heading()
    if err > 180:
        err -= 360
    if err < -180:
        err += 360
    if specificdir != '':
        if specificdir == Direction.CLOCKWISE:
            if err < 0:
                err += 360
        elif specificdir == Direction.COUNTERCLOCKWISE:
            if err > 0:
                err -= 360

    while err > precision or err < -precision:
        update_odometry()
        err = angle - hub.imu.heading()
        if err > 180:
            err -= 360
        elif err < -180:
            err += 360
        if specificdir != '':
            if specificdir == Direction.CLOCKWISE:
                if err < 0:
                    err += 360
            elif specificdir == Direction.COUNTERCLOCKWISE:
                if err > 0:
                    err -= 360
        turnrate = max(-speed, min(speed, err * 2.0))
        if abs(turnrate) < 25:
            if err > 0:
                turnrate = 25
            else:
                turnrate = -25
        robot.drive(0, turnrate)
        wait(20)
  
    robot.stop()

def clearslot(slot):
    slotoffset = slot * bytesperprogram
    writeflash(slotoffset, bytes([0] * bytesperprogram))

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
    global tracking, editmode, selectedslot
    if tracking:
        tracking = False
    elif editmode:
        if selectedslot == 24:
            editmode = False
        else:
            clearslot(selectedslot)
            reset_odometry()
            tracking = True
            updatelastangles()
            editmode = False
    else:
        if selectedslot == 24:
            editmode = True
            selectedslot = 0
        else:
            if not editmode:

                runprogram(selectedslot)


def runprogram(slot):
    reset_odometry()
    global bytesperprogram, selectedslot
    # EVERY instruction has 8 bytes. Every bite consists of eight bits (0 or 1)
    # The first byte contains the type of instruction (from 0 to 255)
    # A byte is SIGNED if it can also contain negative numbers, UNSIGNED if only positive
    # Byte 2 and 3 is parameter 1, byte 4 and 5 parameter 2, byte 6, 7 and 8 are 'flags'.
    # Flags are for small extras like reverse or not.
    data = loadslot(slot)
    for i in range(0, bytesperprogram // 8):

    
        curroffset = 8 * i
        print("RAW BYTES:", list(data[:24]))
        cmd, p1, p2, flag1, flag2, flag3 = ustruct.unpack(">BhhBBB", data[curroffset : curroffset + 8])
       
        if cmd == 0:
            break
        elif cmd == 1:
            drive_to(p1, p2, flag1, flag2)
        elif cmd == 2:
            turnto(p1, flag1, flag2, flag3)
        elif cmd == 3:
            playmotorsnapshot(p1, p2, flag1, flag2, flag3)
    robot.stop()
    print("program finished")
    tracking = False
    running = False
    editmode = False
           

def saveinstruction(slot, cmd, p1, p2, flag1, flag2, flag3):
    offset = countinstructions(slot)
    totaloffset = (offset * 8) + (bytesperprogram * slot)
    data = ustruct.pack(">BhhBBB", cmd, p1, p2, flag1, flag2, flag3)
    writeflash(totaloffset, data)

def countinstructions(slot):
    data = loadslot(slot)
    count = 0
    for offset in range(0, bytesperprogram, 8):
        cmd = data[offset]  # Byte 0 is het type instructie
        if cmd == 0:
            break
        count += 1
    return count
def playmotorsnapshot(p1, p2, flag1, flag2, flag3):
    for idx, (name, m) in enumerate(aux_motors):
        if name is None:
            continue
        try:
            if flag1 & (1 << idx):
                target = p1 if idx == 0 else p2
                m.run_target(flag2, target, wait=flag3)
        except:
            print("Error with playmotorsnapshot")
    
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
    if tracking or tick == 5 and not running:
        print(str(x) + " " + str(y))
        tick = 0
    update_odometry()
    updateinterface()
    newdata = peekinline()
    if newdata != None: 
        processcommand(newdata)
    
    if Button.CENTER in pressed_now:
        if tracking:
            reset_odometry()
            tracking = False
            editmode = False
        else:
            selectslot()
        

    if Button.RIGHT in pressed_now:
        if tracking:

            saveinstruction(selectedslot, 1, int(x), int(y), 250, 15, 0)
            
        else:
            if selectedslot == 24:
                selectedslot = 0
            elif selectedslot >= maxprograms:
                selectedslot = 24
            else:
                selectedslot = selectedslot + 1
        
        

    if Button.LEFT in pressed_now:
        if tracking:
            shot = motorsnapshot(300, 1)
            if shot is not None:
                totaloffset = (countinstructions(selectedslot) * 8) + (bytesperprogram * selectedslot)
                writeflash(totaloffset, shot)
        else:
            if selectedslot <= 0:
                selectedslot = 24
            elif selectedslot == 24:
                selectedslot = maxprograms
            else:
                selectedslot = selectedslot - 1    
    

    wait(20)

    


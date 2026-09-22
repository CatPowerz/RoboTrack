
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

wheeldiameter = 81.6
axle = 140 # distance between left and right wheel

bytesperprogram = 640 # standard config for custom 8 kb robotrack pybricks firmware.
maxprograms = 12


robot = DriveBase(leftmotor, rightmotor, wheeldiameter, axle)

global aux_motors, aux_last_angles

aux_motors = []
aux_last_angles = {}

nowtracking = True
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
    
currentslot = 0
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

    rad = angle * pi / 180

    x += difference * cos(rad)
    y += difference * sin(rad)

    # so basically because you know the robot heading and the distance he travelled you can know where it went

    return x, y, angle

def reset_odometrie():
    global x, y, last_distance
    x = 0.0
    y = 0.0
    hub.imu.reset_heading(0)
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
    if speed == '':
        speed = 10
    update_odometry()
    differencex = tx-x
    differencey = ty-y
    distance=sqrt(differencex**2 + differencey**2)
    while distance > precision:
        update_odometry()
        differencex = tx-x
        differencey = ty-y
        distance=sqrt(differencex**2 + differencey**2)
        tangle = atan2(differencey, differencex) * 180 / pi
        
        err = tangle - hub.imu.heading()
        if err > 180:
            err -= 360
        if err < -180:
            err += 360
        if speed < 0:
            err = -err
        robot.drive(speed, err)

    robot.stop()

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
        if speed > 2:
            speed = 2
        err = err * speed
        robot.drive(0, err)
        wait(10)
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
            tracking = True
            editmode = False
    else:
        if selectedslot == 24:
            editmode = True
            selectedslot = 0
        else:
            if not editmode:

                runprogram(selectedslot)


def runprogram(slot):
    global bytesperprogram, selectedslot
    # EVERY instruction has 8 bytes. Every bite consists of eight bits (0 or 1)
    # The first byte contains the type of instruction (from 0 to 255)
    # A byte is SIGNED if it can also contain negative numbers, UNSIGNED if only positive
    # Byte 2 and 3 is parameter 1, byte 4 and 5 parameter 2, byte 6 and 7 parameter 3 (speed)
    # Final byte is for small extras like reverse or not.
    data = loadslot(slot)
    for i in range(0, bytesperprogram // 8):

    
        curroffset = 8 * i
    
        cmd, p1, p2, p3, flag = ustruct.unpack(">BhhhB", data[curroffset : curroffset + 8])
        
        if cmd == 0:
            break

while True:
    update_odometry()
    updateinterface()
    updatelastangles()
    newdata = peekinline()
    if newdata != None:
        processcommand(newdata)
    
    if Button.CENTER in hub.buttons.pressed():
        selectslot()
        while Button.CENTER in hub.buttons.pressed():
            wait(20)

    if Button.RIGHT in hub.buttons.pressed():
        if tracking:
            wait(20)
        else:
            if selectedslot == 24:
                selectedslot = 0
            elif selectedslot >= maxprograms:
                selectedslot = 24
            else:
                selectedslot = selectedslot + 1
        
        while Button.RIGHT in hub.buttons.pressed():
            wait(20)

    if Button.LEFT in hub.buttons.pressed():
        if tracking:
            wait(20)
        else:
            if selectedslot <= 0:
                selectedslot = 24
            elif selectedslot == 24:
                selectedslot = maxprograms
            else:
                selectedslot = selectedslot - 1
            
            while Button.LEFT in hub.buttons.pressed():
                wait(20)
    
    

    wait(20)

    



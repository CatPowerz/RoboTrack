# RoboTrack

A full telemetry, odometry tracking, and debugging system for FIRST LEGO League (FLL) robots. Built for our team, **REborn** (Bornego College), running on a LEGO SPIKE Prime hub with custom Pybricks firmware and a Flutter desktop app over BLE.

---

## Please watch the demo video before trying the project!
[![Watch Demo Video](https://img.shields.io/badge/YouTube-Watch%20Demo%20Video%20-red?style=for-the-badge&logo=youtube)](https://youtu.be/S3cDEyh_7lM)

## Why we built this

If you've ever tried building a serious competition robot with the stock LEGO SPIKE app, you know the pain:
- The stock app is laggy, slow to upload, and locks you into a clunky block/hybrid environment that feels like a toy.
- Robot runs are inconsistent. You tweak a turn, run it on the mat, and it ends up somewhere completely different because wheel slip and heading drift are impossible to catch.
- When an autonomous run fails, you're literally just staring at the mat guessing why. Did a wheel slip? Did the gyro drift? Did a motor stall? There's zero real-time feedback.

Pybricks makes the robot run 10x smoother with proper MicroPython support, but doing high-speed odometry and live tracking out of the box had a major catch: standard BLE buffers on the hub are tiny, so streaming real-time coordinates, motor speeds, and battery stats instantly clogged the connection and dropped packets.

RoboTrack is our complete fix for all of this.

---

## How it works

Instead of guessing, the robot tracks its exact position and talks straight to our laptop in real time:

1. **Custom Pybricks C Firmware**: We patched and recompiled Pybricks firmware to boost the internal BLE ring buffer to 8 KB, so the hub never drops data packets when spamming live sensor updates.
2. **Onboard Odometry & Logic (`robotrack.py`)**: A dedicated MicroPython script on the hub running our motion logic, gyro-assisted driving, coordinate math (X/Y position tracking), and state management.
3. **Flutter Desktop App**: A custom dashboard where we can see the robot drive across a virtual competition field live, compare runs, catch wheel slips, and send commands back over BLE.

---

## Standalone & With Computer

Obviously, since communication with the robot during the run is illegal in an official tournament, the robot can write its runs to its flash memory storage and can both **run and record** instructions without a device.

## Communication & Protocol

We didn't want the overhead of heavy JSON strings slowing down the hub loop, so we built our own lightweight communication layer:

- **Robot Internal (Flash Storage Instruction Packets)**:  
  Every run is saved directly to flash memory in compact **8-byte binary packets** using `>BhhBBB` struct packing:
  - **Byte 0** (`uint8`): **Command / Instruction Type** (`0` = EOF, `1` = Drive To, `2` = Turn To, `3` = Motor Snapshot)
  - **Bytes 1–2** (`int16`): **Parameter 1** (e.g. Target X coordinate, target heading, or Motor 1 angle)
  - **Bytes 3–4** (`int16`): **Parameter 2** (e.g. Target Y coordinate or Motor 2 angle)
  - **Byte 5** (`uint8`): **Flag 1** (e.g. Speed, motor change mask)
  - **Byte 6** (`uint8`): **Flag 2** (e.g. Position tolerance, motor speed)
  - **Byte 7** (`uint8`): **Flag 3** (e.g. Direction override mode, wait-for-completion flag)
    
- **Robot → Computer (Telemetry)**: 

 The robot constantly prints ```{x},{y},{robot_heading},{robot_pitch},{robot_roll},{capacity},{mask}```
 For short, it prints all telemetry data like position, rotation and even battery capacity.
  
The Flutter app listens, decodes these values into a class, and plots the live path on screen.

- **Computer → Robot (Commands)**:  
  Commands use a simple string format over BLE: `type|parameter` (like sending `SHUTDOWN` or run triggers).

---

## Repo Structure

- `flutter-app/`: The Flutter desktop code for the live dashboard, field UI, and BLE listener.
- `python-robot/`: `robotrack.py`, the main robot script with the odometry loops, motor control, and telemetry packet builder.
- `custom-firmware-src/`: The modified Pybricks MicroPython C source code with our enlarged buffer patch.
- `firmware-compiled-build/`: Ready-to-flash binary builds of our custom firmware.

---

## Setup & Running

### 1. Hub Firmware
Flash the pre-compiled firmware located in `firmware-compiled-build/` using the official Pybricks web installer (or flash from source via the build scripts in `custom-firmware-src/`).

### 2. Robot Code
Deploy `python-robot/robotrack.py` to the SPIKE Prime hub using the Pybricks IDE.

### 3. Desktop App
You can easily run `desktopapp/robotrack.exe` to launch the app and either connect to a robot over BLE or connect to a virtual robot.

If you want to compile it yourself, ensure Flutter is installed on your development machine, then run:

```bash
cd flutter-app
flutter pub get
flutter run -d windows
```
Turn on the SPIKE Prime hub, connect via BLE in the desktop interface, and start a run.

1. **Flash Firmware**: Flash the pre-compiled binary from `firmware-compiled-build/` onto the SPIKE Prime hub using the Pybricks web tool.
2. **Upload Robot Code**: Copy `python-robot/robotrack.py` into the Pybricks IDE and download it to the hub.
3. **Launch Desktop App**:
   ```bash
   cd flutter-app
   flutter pub get
   flutter run -d windows
   ```
Turn on the hub, hit connect in the Flutter app or connect to a virtual robot, and place the robot on the mat.

Tech Stack
Firmware: C / MicroPython (Pybricks)

Robot Brain: MicroPython

Desktop UI: Flutter (Dart)

Connection: Bluetooth Low Energy (BLE)


**Author: Quintijn (@CatPowerz)**

Please do not copy the app and call it yours.
Feel free to look at our code and architecture for inspiration! However, please do not clone/copy this into your own team's project. FLL judges ask deep technical questions about your software, and you must understand and write your own code to explain it.

(C) Quintijn / REborn: All Rights Reserved

"LEGO® and SPIKE™ are trademarks of the LEGO Group. Flutter is a trademark of Google LLC. This project is independent and not affiliated with or endorsed by these entities."

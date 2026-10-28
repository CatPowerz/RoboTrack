# RoboTrack

Real-time telemetry and odometry tracking system for FIRST LEGO League (FLL) robots using a LEGO SPIKE Prime hub, custom Pybricks firmware, and a Flutter desktop dashboard over Bluetooth Low Energy (BLE).

Built for team REborn (Bornego College) for the FLL season.

---

## The Problem & Motivation

Standard LEGO SPIKE Prime firmware has limited bandwidth and lacks practical, high-frequency bidirectional telemetry during run testing. Pybricks solves the execution speed and control precision, but by default its internal BLE buffer is restricted to standard small MTU sizes, causing packet drops when streaming continuous odometry data (X/Y coordinates, gyro heading, motor velocity, and sensor logs) at high sample rates.

RoboTrack solves this with three connected parts:
1. Custom Pybricks firmware compiled with an extended 8 KB telemetry buffer.
2. An onboard Python runtime script handling motion profiles and binary-packed BLE packet dispatch.
3. A cross-platform Flutter desktop dashboard running real-time field visualization, run comparisons, and replay logs.

---

## Architecture Overview

[ LEGO SPIKE Prime Hub ]
│
├─ custom-firmware-src/   → Pybricks C source (8 KB ring buffer patch)
│
└─ python-robot/          → Pybricks Python script
│
│  (BLE Telemetry Stream: 8-byte packed packets)
▼
[ Host Machine (Windows/Linux) ]
│
└─ flutter-app/           → Desktop dashboard (live plotting & odometry)


---

## Repository Structure

- `flutter-app/`: Cross-platform Flutter desktop client. Connects directly to the hub via BLE, parses incoming telemetry packets, and renders real-time coordinate paths on the competition field.
- `python-robot/`: The onboard robot control script (`robotrack.py`). Implements motion scheduling, gyro-compensated drive routines, and real-time sensor polling.
- `custom-firmware-src/`: Patched Pybricks MicroPython firmware source. Contains the modified internal buffer size to prevent buffer overruns during sustained telemetry broadcasts.
- `firmware-compiled-build/`: Pre-compiled binary builds of the custom firmware ready to flash directly onto the SPIKE Prime hub.

---

## Telemetry Protocol

To maintain low latency and prevent BLE packet fragmentation, telemetry data is packed into 8-byte structured binary payloads instead of JSON or string serialization:

- **Byte 0**: Instruction / Message Type (0–255)
- **Byte 1**: Signed flags (execution state, tracking status)
- **Bytes 2–3**: Parameter 1 (16-bit integer, e.g., X position / linear velocity)
- **Bytes 4–5**: Parameter 2 (16-bit integer, e.g., Y position / target heading)
- **Bytes 6–7**: Auxiliary flags & run metadata

This keeps throughput high and parsing overhead on the host machine negligible.

---

## Getting Started

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
flutter run -d windows```
Turn on the SPIKE Prime hub, connect via BLE in the desktop interface, and start a run.

Tech Stack
Firmware: C / MicroPython (Pybricks runtime)

Robot Script: MicroPython

Desktop Application: Flutter / Dart

Communication: Bluetooth Low Energy (BLE)

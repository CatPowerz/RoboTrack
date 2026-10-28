import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:robotrack/classes/telemetrydata.dart';
import 'package:robotrack/widgets/visualisationwidget.dart';
import 'dart:async';
import 'dart:math';

import 'package:robotrack/widgets/visualisationyawpitchroll.dart';
import 'package:universal_ble/universal_ble.dart';

class MainDashboard extends StatefulWidget {
  const MainDashboard({super.key});

  @override
  State<MainDashboard> createState() => _MainDashboardState();
}

class _MainDashboardState extends State<MainDashboard> {
  int selectedIndex = 0;
  double camX = 0.0;
  double camY = 0.0;
  double simPitch = 0.0;
  double simRoll = 0.0;
  Timer? mocktimer;
  double mockangle = 0.0;
  double simTime = 0.0;
  final List<Offset> trail = [];
  List<BleDevice> devicesList = [];
  bool isScanning = false;
  String bleBuffer = "";
  BleDevice? connectedHub;
  int packets = 0;
  int packetspersecond = 0;
  bool chargingstate = false;
  int activeRunSlot = 1;
  final String uartServiceUuid = "c5f50001-8280-46da-89f4-6d8051e4aeef";
  final String uartTxUuid = "c5f50002-8280-46da-89f4-6d8051e4aeef";
  final String uartRxUuid      = "c5f50002-8280-46da-89f4-6d8051e4aeef";
  int mockbattery = 95;
  final Map<String, DateTime> _lastSeen = {};
  Timer? _cleanupTimer;
  Timer? _telemetryUpdateTimer;
  TelemetryData? _pendingTelemetry;
  late final ValueNotifier<TelemetryData> _telemetryListenable =
      ValueNotifier<TelemetryData>(telemetry);
  final Set<String> _knownRobotIds = {};
  void startContinuousScan() async {
    if (isScanning || selectedIndex != 0) return;


    setState(() {
      devicesList.clear();
      isScanning = true;
    });

    await UniversalBle.startScan();
  }

  void stopContinuousScan() async {

    if (!isScanning) return;

    await UniversalBle.stopScan();

    if (mounted) {
      setState(() {
        isScanning = false;
      });
    }
  }

  Timer? packettimer;
  Timer? batterytimer;
  void _handleDisconnect() {
  if (!mounted) return;

  connectedHub = null;

  resetAllTelemetryData();

  setState(() {
    selectedIndex = 0;
  });

  startContinuousScan();
}
DateTime _lastPacketReceived = DateTime.now();
Timer? _heartbeatWatchdog;

void _startHeartbeatWatchdog() {
  _heartbeatWatchdog?.cancel();
  _lastPacketReceived = DateTime.now();

  _heartbeatWatchdog = Timer.periodic(const Duration(milliseconds: 500), (timer) {
    if (connectedHub == null || selectedIndex != 1) {
      timer.cancel();
      return;
    }

    if (DateTime.now().difference(_lastPacketReceived).inMilliseconds > 1200) {
     
      timer.cancel();
      _handleDisconnect();
    }
  });
}
  @override
  void initState() {
    super.initState();
    packettimer = Timer.periodic(const Duration(seconds: 1), (timer) {
      setState(() {
        packetspersecond = packets;

        packets = 0;

      });
    });
    batterytimer = Timer.periodic(const Duration(seconds: 10), (timer) {
      if (!mocking) return;

      if (chargingstate) {
        mockbattery = (mockbattery + 1).clamp(10, 100).toInt();
        if (mockbattery == 100) chargingstate = false;
      } else {
        mockbattery = (mockbattery - 1).clamp(10, 100).toInt();
        if (mockbattery == 10) chargingstate = true;
      }
    });
    UniversalBle.onScanResult = (bleDevice) {
      final name = bleDevice.name;
      if (name == null || name.isEmpty) return;

      _lastSeen[bleDevice.deviceId] = DateTime.now();

      final isRobotNow =
          bleDevice.services.any((s) {
            final lower = s.toLowerCase();
            return lower.contains("6e400001") || lower.contains("c5f50001");
          }) ||
          name.toLowerCase().contains("robotrack") ||
          name.toLowerCase().contains("pybricks") ||
          name.toLowerCase().contains("spike");

      if (isRobotNow) {
        _knownRobotIds.add(bleDevice.deviceId);
      }
      UniversalBle.onConnectionChange = (String deviceId, bool isConnected, String? error) {
    if (connectedHub != null && deviceId == connectedHub!.deviceId && !isConnected) {
  
      _handleDisconnect();
    }
  };
  

  
      

      final index = devicesList.indexWhere(
        (d) => d.deviceId == bleDevice.deviceId,
      );

      if (index == -1) {
        setState(() {
          devicesList.add(bleDevice);
        });
      } else {
        final existing = devicesList[index];
        // Alleen updaten als de naam daadwerkelijk verandert
        if (existing.name != bleDevice.name) {
          setState(() {
            devicesList[index] = bleDevice;
          });
        }
      }
    };

    _cleanupTimer = Timer.periodic(const Duration(seconds: 2), (_) {
      final now = DateTime.now();
      final staleIds = devicesList
          .where((device) {
            final lastTime = _lastSeen[device.deviceId];
            return lastTime == null || now.difference(lastTime).inSeconds > 5;
          })
          .map((device) => device.deviceId)
          .toSet();
      if (staleIds.isEmpty) return;

      for (final deviceId in staleIds) {
        _lastSeen.remove(deviceId);
      }
      if (mounted) {
        setState(() {
          devicesList.removeWhere(
            (device) => staleIds.contains(device.deviceId),
          );
        });
      }
    });

    UniversalBle.onValueChange =
        (deviceId, characteristicId, rawBytes, serviceId) {
          _lastPacketReceived = DateTime.now();
          if (rawBytes.isEmpty || rawBytes[0] != 1) return;
          _handleIncomingData(rawBytes.sublist(1));
        };

    startContinuousScan();
  }


  @override
  void dispose() {
    mocktimer?.cancel();
    batterytimer?.cancel();
    packettimer?.cancel();
    _cleanupTimer?.cancel();
    _telemetryUpdateTimer?.cancel();
    _telemetryListenable.dispose();
    UniversalBle.onScanResult = null;
    UniversalBle.onValueChange = null;
    UniversalBle.onConnectionChange = null;
    super.dispose();
  }

 void _queueTelemetryUpdate(TelemetryData nextTelemetry) {
  _pendingTelemetry = nextTelemetry;
  if (_telemetryUpdateTimer != null) return;

  _telemetryUpdateTimer = Timer(const Duration(milliseconds: 33), () {
    _telemetryUpdateTimer = null;
    final next = _pendingTelemetry;
    _pendingTelemetry = null;
    if (!mounted || next == null) return;

    telemetry = next;
    trail.add(Offset(next.xpos, next.ypos));
    if (trail.length > 50) trail.removeAt(0);
    camX += (next.xpos - camX) * 0.1;
    camY += (next.ypos - camY) * 0.1;
    
    _telemetryListenable.value = next;
  });
}
  void resetAllTelemetryData() {
    mocktimer?.cancel();
    mocking = false;
    mocktimer = null;
    _telemetryUpdateTimer?.cancel();
    _telemetryUpdateTimer = null;
    _pendingTelemetry = null;

    setState(() {
      robotX = 0.0;
      robotY = 0.0;
      heading = 0.0;
      turnRate = 0.0;
      simTime = 0.0;
      simPitch = 0.0;
      simRoll = 0.0;
      mockangle = 0.0;
      camX = 0.0;
      camY = 0.0;

      trail.clear();
      bleBuffer = "";

      telemetry = const TelemetryData(
        yaw: 0.0,
        pitch: 0.0,
        roll: 0.0,
        xpos: 0.0,
        ypos: 0.0,
        batterylevel: 100,
        occupiedslots: {},
        leftwheelport: 'A',
        rightwheelport: 'B',
        maxslots: '12',
        bytesperprogram: '0',
      );
      _telemetryListenable.value = telemetry;
    });
  }

  void connectToHub(BleDevice device) async {
 
    stopContinuousScan();
    await UniversalBle.stopScan();
    await Future.delayed(const Duration(milliseconds: 250));

    try {
      setState(() {
        isScanning = false;
        resetAllTelemetryData();
        selectedIndex = 1;
      });

      print("Verbinden met ${device.deviceId}...");

      final Completer<bool> connectionCompleter = Completer<bool>();

      UniversalBle.onConnectionChange = (deviceId, isConnected, error) {
        if (deviceId == device.deviceId && isConnected) {
          if (!connectionCompleter.isCompleted) {
            connectionCompleter.complete(true);
          }
        }
      };

      await UniversalBle.connect(device.deviceId);
      _startHeartbeatWatchdog();
      connectedHub = device;

      await connectionCompleter.future.timeout(
        const Duration(seconds: 8),
        onTimeout: () => throw Exception("Time-out: verbinding duurde te lang"),
      );

      print("Verbonden! Korte pauze voor GATT caching...");
      await Future.delayed(const Duration(milliseconds: 1000));

      print("Notificaties aanzetten op Nordic UART...");
      await UniversalBle.setNotifiable(
        device.deviceId,
        uartServiceUuid,
        uartTxUuid,
        BleInputProperty.notification,
      );

      print("Klaar! Telemetrie actief.");
      final services = await UniversalBle.discoverServices(device.deviceId);
for (var s in services) {
  print("Service: ${s.uuid}");
  for (var c in s.characteristics) {
    print("  -> Char: ${c.uuid} (properties: ${c.properties})");
  }
}

    } catch (e, stack) {
      print("CRASH IN CONNECT: $e");
      print(stack);
      if (mounted) {
        setState(() {
          selectedIndex = 0;
        });
        startContinuousScan();
      }
    }
  }
  TelemetryData telemetry = const TelemetryData(
    yaw: 0.0,
    pitch: 0.0,
    roll: 0.0,
    xpos: 0.0,
    ypos: 0.0,
    batterylevel: 100,
    occupiedslots: {},
    leftwheelport: 'A',
    rightwheelport: 'B',
    maxslots: '12',
    bytesperprogram: '0',
  );
  double normalizedYaw(double rad) {
    double deg = (rad * 180 / pi) - 90;
    deg = (deg + 180) % 360;
    if (deg < 0) deg += 360;
    return deg - 180;
  }

  double radToDeg(double rad) {
    return rad * 180 / pi;
  }
  Future<void> sendCommand(String command) async {
  if (connectedHub == null) {
  return;
  }

  try {
   
    final data = utf8.encode("$command\n");
    final commandBytes = utf8.encode("$command\n");
    final payload = Uint8List(commandBytes.length + 1);
    payload[0] = 0x06; // 0x06 = Pybricks command voor sys.stdin!
    payload.setRange(1, payload.length, commandBytes);
    await UniversalBle.writeValue(
      connectedHub!.deviceId,
      uartServiceUuid,
      uartRxUuid,
      Uint8List.fromList(payload),
      BleOutputProperty.withResponse,
    );
    if (data == utf8.encode("SHUTDOWN\n")) {
      connectedHub = null;
    }


  } catch (e) {
    print(e);
  }
}
  @override
  Widget build(BuildContext context) {
    final List<Widget Function()> pageBuilders = [
      () => Center(
        child: SingleChildScrollView(
          padding: const EdgeInsets.symmetric(vertical: 32, horizontal: 16),
          child: ConstrainedBox(
            constraints: const BoxConstraints(maxWidth: 700),
            child: Column(
              children: [
                Card(
                  child: Padding(
                    padding: EdgeInsets.all(24),
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: [
                        const SizedBox(height: 24),
                        FractionallySizedBox(
                          widthFactor: 0.8,

                          child: Image.asset('assets/rebornrobotrack.png'),
                        ),
                        Text(
                          'Welcome to REborn RoboTrack!',
                          style: TextStyle(
                            fontFamily: "Orbitron",
                            fontSize: 24,
                          ),
                          textAlign: TextAlign.center,
                        ),
                        Text(
                          'Connect your SPIKE Prime robot with RoboTrack firmware',
                          style: TextStyle(
                            fontFamily: "Orbitron",
                            fontSize: 18,
                          ),
                          textAlign: TextAlign.center,
                        ),
                        const SizedBox(height: 24),
                        Text('Automatically scanning for Bluetooth-devices...', textAlign: TextAlign.center, style: TextStyle(fontFamily: 'Orbitron', fontSize: 12)),
                        const SizedBox(height: 24),
                      ],
                    ),
                  ),
                ),

                const SizedBox(height: 12),
                Card(
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: [
                      ...devicesList.map((device) {
                        final name = device.name;
                        if (name != null && device.name!.isNotEmpty) {
                          final bool isRobot =
                              device.services.any(
                                (s) =>
                                    s.toLowerCase().contains("6e400001") ||
                                    s.toLowerCase().contains("c5f50001"),
                              ) ||
                              _knownRobotIds.contains(device.deviceId);
                          if (isRobot) {
                            _knownRobotIds.add(device.deviceId);
                            return Container(
                              key: ValueKey(device.deviceId),
                              decoration: BoxDecoration(
                                border: Border.all(
                                  color: Colors.white.withValues(alpha: 0.5),
                                ),
                                borderRadius: BorderRadius.circular(8),
                                color: Colors.white.withValues(alpha: 0.1),
                              ),
                              child: ListTile(
                                leading: const Icon(
                                  Icons.bluetooth,
                                  color: Colors.teal,
                                ),

                                title: Text(
                                  name,
                                  style: TextStyle(fontFamily: 'Orbitron'),
                                ),
                                onTap: () {
                                  connectToHub(device);
                                },
                              ),
                            );
                          } else {
                            return Container(
                              key: ValueKey(device.deviceId),
                              decoration: BoxDecoration(
                                border: Border.all(
                                  color: Colors.white.withValues(alpha: 0.1),
                                ),
                                
                                borderRadius: BorderRadius.circular(8),
                                color: Colors.white.withValues(alpha: 0.0001),
                              ),
                              child: ListTile(
                                leading: const Icon(
                                  Icons.bluetooth_disabled,
                                  color: Color.fromARGB(150, 158, 158, 158),
                                ),

                                title: Text(
                                  name,
                                  style: TextStyle(fontFamily: 'Orbitron'),
                                ),
                              ),
                            );
                          }
                        } else {
                          return SizedBox.shrink();
                        }
                      }),
                    ],
                  ),
                ),
                const SizedBox(height: 12),

                Card(
                  child: Padding(
                    padding: EdgeInsets.all(24),
                    child: Column(
                      children: [
                        const SizedBox(height: 12),
                        Text(
                          "Don't have a SPIKE Prime robot?",
                          style: TextStyle(
                            fontSize: 24,
                            fontFamily: 'Orbitron',
                          ),
                        ),
                        const SizedBox(height: 12),
                        FilledButton.icon(
                          onPressed: () {
                            setState(() {
                              showDialog(
                                context: context,
                                builder: (context) {
                                  return AlertDialog(
                                    title: Text("Emulate SPIKE robot?"),
                                    content: SizedBox(
                                      height: 50,
                                      child: Column(
                                        children: [
                                          Text(
                                            'A virtual SPIKE robot will be connected. The robot has no physical flash/storage, so data will not save.',
                                          ),
                                          Text(
                                            'The robot will drive around randomly like on any other mat. You cannot control the robot but you can read/analyse it.',
                                          ),
                                        ],
                                      ),
                                    ),
                                    actions: [
                                      FilledButton(
                                        onPressed: () {
                                          Navigator.of(context).pop();
                                        },
                                        child: Icon(Icons.cancel),
                                      ),
                                      FilledButton(
                                        onPressed: () {
                                          selectedIndex = 1;
                                          startMockTelemetry();
                                          Navigator.of(context).pop();
                                        },
                                        child: Icon(Icons.check),
                                      ),
                                    ],
                                  );
                                },
                              );
                            });
                          },

                          icon: Icon(Icons.play_arrow),
                          label: Text(
                            'START VIRTUAL ROBOT',
                            style: TextStyle(
                              fontSize: 24,
                              fontFamily: 'Orbitron',
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
              ],
            ),
          ),
        ),
      ),


      () => ValueListenableBuilder<TelemetryData>(
        valueListenable: _telemetryListenable,
        builder: (context, currentTelemetry, child) => Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Expanded(flex: 3, child: Image.asset('assets/rebornrobotrack.png')),
            Expanded(
              flex: 17,
              child: Row(
                children: [

                  Expanded(
                    flex: 4,
                    child: SizedBox.expand(
                      child: RepaintBoundary(
                        child: CustomPaint(
                          painter: FieldPainter(
                            xpos: currentTelemetry.xpos,
                            ypos: currentTelemetry.ypos,
                            yaw: mocking ? -currentTelemetry.yaw : currentTelemetry.yaw,
                            pitch: currentTelemetry.pitch,
                            roll: currentTelemetry.roll,
                            camX: camX,
                            camY: camY,
                            trail: trail,

                          ),
                        ),
                      ),
                    ),
                  ),
                  Expanded(
                    flex: 3,
                    child: SingleChildScrollView(
                      child: Padding(
                        padding: const EdgeInsets.all(28.0),

                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.stretch,
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            Card(
                              child: Padding(
                                padding: const EdgeInsets.all(8.0),
                                child: Row(
                                  crossAxisAlignment: CrossAxisAlignment.center,
                                  children: [
                                    const Icon(
                                      Icons.battery_0_bar,

                                      color: Colors.tealAccent,
                                      size: 48,
                                    ),
                                    const SizedBox(width: 8),
                                    Expanded(

                                      child: SizedBox(
                                        height: 18,
                                        child: ClipRRect(
                                          borderRadius: BorderRadius.circular(
                                            4,
                                          ),
                                          child: LinearProgressIndicator(
                                            value:
                                                currentTelemetry.batterylevel /
                                                100,
                                            color: Colors.tealAccent,
                                            backgroundColor: Colors.white24,
                                          ),
                                        ),
                                      ),
                                    ),
                                    const SizedBox(width: 12),
                                    Text(
                                      '${currentTelemetry.batterylevel}%',
                                      style: const TextStyle(fontSize: 28),
                                    ),
                                  ],
                                ),
                              ),
                            ),
                            Card(
                              child: Padding(
                                padding: const EdgeInsets.all(16.0),
                                child: Column(
                                  children: [
                                    Text('3D', style: TextStyle(fontSize: 48)),
                                    AttitudeVisualisation(
                                      pitch: currentTelemetry.pitch,
                                      roll: currentTelemetry.roll,
                                      yaw: normalizedYaw(currentTelemetry.yaw),
                                      size: 300,
                                    ),
                                  ],
                                ),
                              ),
                            ),
                          ],
                        ),
                      ),
                    ),
                  ),

                  Expanded(
                    flex: 3,
                    child: SingleChildScrollView(
                      child: Padding(
                        padding: const EdgeInsets.all(28.0),

                        child: FractionallySizedBox(
                          child: Column(
                            crossAxisAlignment: CrossAxisAlignment.center,
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              Center(
                                child: Row(
                                  children: [
                                    Expanded(
                                      child: Card(
                                        child: Padding(
                                          padding: const EdgeInsets.all(8.0),
                                          child: FittedBox(
                                            fit: BoxFit.scaleDown,
                                            child: Text(
                                              'X: ${(currentTelemetry.xpos / 10).toStringAsFixed(1)}',
                                              style: const TextStyle(
                                                fontSize: 48,
                                              ),
                                            ),
                                          ),
                                        ),
                                      ),
                                    ),
                                    const SizedBox(width: 8),
                                    Expanded(
                                      child: Card(
                                        child: Padding(
                                          padding: const EdgeInsets.all(8.0),
                                          child: FittedBox(
                                            fit: BoxFit.scaleDown,
                                            child: Text(
                                              'Y: ${(currentTelemetry.ypos / 10).toStringAsFixed(1)}',
                                              style: const TextStyle(
                                                fontSize: 48,
                                              ),
                                            ),
                                          ),
                                        ),
                                      ),
                                    ),
                                  ],
                                ),
                              ),
                              Center(),
                              Card(
                                child: Padding(
                                  padding: const EdgeInsets.all(8.0),
                                  child: SizedBox(
                                    width: 400,
                                    child: Text(
                                      'Yaw: ${normalizedYaw(currentTelemetry.yaw).toStringAsFixed(1)}°',
                                      textAlign: TextAlign.center,
                                      style: TextStyle(fontSize: 48),
                                    ),
                                  ),
                                ),
                              ),
                              Card(
                                child: Padding(
                                  padding: const EdgeInsets.all(8.0),
                                  child: SizedBox(
                                    width: 400,
                                    child: Text(
                                      'Pitch: ${currentTelemetry.pitch.round()}°',
                                      textAlign: TextAlign.center,
                                      style: TextStyle(fontSize: 48),
                                    ),
                                  ),
                                ),
                              ),
                              Card(
                                child: Padding(
                                  padding: const EdgeInsets.all(8.0),
                                  child: SizedBox(
                                    width: 400,
                                    child: Text(
                                      'Roll: ${currentTelemetry.roll.round()}°',
                                      textAlign: TextAlign.center,
                                      style: TextStyle(fontSize: 48),
                                    ),
                                  ),
                                ),
                              ),
                              Card(
                                child: Padding(
                                  padding: const EdgeInsets.all(8.0),
                                  child: SizedBox(
                                    width: 400,
                                    height: 100,
                                    child: Column(
                                      children: [
                                        Text(
                                          mocking
                                              ? "Virtual Robot Connected"
                                              : "Live Robot Connected",
                                          textAlign: TextAlign.center,
                                          style: TextStyle(fontSize: 24),
                                        ),
                                        Row(
                                          crossAxisAlignment:
                                              CrossAxisAlignment.baseline,
                                          mainAxisAlignment:
                                              MainAxisAlignment.center,
                                          textBaseline: TextBaseline.alphabetic,
                                          children: [
                                            Text(
                                              "${packetspersecond}",
                                              textAlign: TextAlign.center,
                                              style: TextStyle(fontSize: 36),
                                            ),
                                            Text(
                                              "Hz (packets/second)",
                                              textAlign: TextAlign.center,
                                              style: TextStyle(fontSize: 24),
                                            ),
                                          ],
                                        ),
                                      ],
                                    ),
                                  ),
                                ),
                              ),
                            ],
                          ),
                        ),
                      ),
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
      () => Padding(
        padding: const EdgeInsets.all(38.0),
        child: Card(
          child: Row(
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Expanded(
                child: SizedBox(
                  height: double.infinity,
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: [
                      const SizedBox(height: 16),
                      const Text(
                        "PROGRAM SLOTS",

                        textAlign: TextAlign.center,
                        style: TextStyle(fontSize: 48, fontFamily: 'Orbitron'),
                      ),
                      const Text(
                        "View the occupied slots of your SPIKE robot. The occupied slots are shown in black, while the free slots are shown in white.",
                        textAlign: TextAlign.center,
                        style: TextStyle(fontSize: 16, fontFamily: 'Orbitron'),
                      ),
                      const SizedBox(height: 16),
                      GridView.count(
                        shrinkWrap: true,
                        crossAxisCount: 5,
                        mainAxisSpacing: 6,
                        childAspectRatio: 2,
                        physics: const NeverScrollableScrollPhysics(),
                        children: List.generate(12, (index) {
                          final slotNumber = index + 1;
                          final isOccupied = telemetry.occupiedslots.contains(
                            slotNumber,
                          );
                          return Container(
                            decoration: BoxDecoration(
                              color: isOccupied
                                  ? Colors.black
                                  : Colors.white.withValues(alpha: 0.2),
                              borderRadius: BorderRadius.circular(10),
                              border: Border.all(
                                color: isOccupied
                                    ? Colors.white
                                    : Colors.tealAccent.withValues(alpha: 0.2),
                              ),
                            ),
                            
                              child: Center(
                                child: Text(
                                  "$slotNumber",
                                  style: const TextStyle(
                                    fontSize: 32,
                                    fontFamily: 'Orbitron',
                                  ),
                                ),
                              ),
                            );
                          
                        }),
                      ),
                    ],
                  ),
                ),
              ),
            ],
          ),
        ),
      ),

      
    ];
    return Scaffold(
      backgroundColor: Colors.transparent,
      body: Row(
        children: [
          AnimatedSize(
            duration: const Duration(milliseconds: 400),
            curve: Curves.easeOutCubic,
            child: AnimatedSwitcher(
              duration: const Duration(milliseconds: 400),
              switchInCurve: Curves.easeInCubic,
              switchOutCurve: Curves.easeOutCubic,
              layoutBuilder: (currentChild, previousChildren) {
                return Stack(
                  alignment: Alignment.centerLeft,
                  children: [...previousChildren, ?currentChild],
                );
              },
              transitionBuilder: (child, animation) {
                final slide = Tween<Offset>(
                  begin: const Offset(-1.0, 0.0),
                  end: Offset.zero,
                ).animate(animation);
                return SlideTransition(
                  position: slide,
                  child: FadeTransition(opacity: animation, child: child),
                );
              },
              child: selectedIndex == 0
                  ? const SizedBox.shrink(key: ValueKey('empty_nav'))
                  : NavigationRail(
                      key: const ValueKey('sidebar'),
                      destinations: [
                        NavigationRailDestination(
                          icon: Icon(Icons.home_outlined),
                          label: Text('Home'),
                          selectedIcon: Icon(Icons.home),
                        ),
                        NavigationRailDestination(
                          icon: Icon(Icons.analytics_outlined),
                          label: Text('Analytics'),
                          selectedIcon: Icon(Icons.analytics),
                        ),
                        NavigationRailDestination(
                          icon: Icon(Icons.speed_outlined),
                          label: Text('Runs'),
                          selectedIcon: Icon(Icons.speed),
                        ),
                        
                      ],
                      selectedIndex: selectedIndex.clamp(0, 2),
                      onDestinationSelected: (value) {
                        if (value == 0) {
                          startContinuousScan();
                        } else {
                          stopContinuousScan();
                        }

                        if (value == 0) {
                          showDialog(
                            context: context,
                            builder: (context) {
                              return AlertDialog(
                                title: Text('Are you sure?'),
                                content: Text(
                                  mocking ? "The virtual robot will be disconnected and you'll return to the homepage." : "The robot will be disconnected an you'll return to the homepage.\nThe hub will shut down.",
                                ),
                                actions: [
                                  FilledButton(
                                    onPressed: () {
                                      Navigator.of(context).pop();
                                    },
                                    child: Icon(Icons.cancel),
                                  ),
                                  
                                 FilledButton(
  onPressed: () async {
    setState(() {
      _lastSeen.clear();
      devicesList.clear();
      selectedIndex = value;
    });

    final connectedHub = this.connectedHub;
    if (connectedHub != null) {
      await sendCommand("SHUTDOWN");
      await UniversalBle.disconnect(connectedHub.deviceId);
    }
stopContinuousScan();
   await UniversalBle.stopScan();
   
await Future.delayed(const Duration(milliseconds: 150));
startContinuousScan();
    Navigator.of(context).pop();
  },
  child: const Icon(Icons.check),
),
                                ],
                              );
                            },
                          );
                        } else {
                          setState(() {
                            selectedIndex = value;
                          });
                        }
                      },
                    ),
            ),
          ),

          Expanded(
            child: AnimatedSwitcher(
              duration: const Duration(milliseconds: 250),
              switchInCurve: Curves.easeInCubic,
              switchOutCurve: Curves.easeOutCubic,

              child: KeyedSubtree(
                key: ValueKey<int>(selectedIndex),
                child: pageBuilders[selectedIndex](),
              ),
              transitionBuilder: (child, animation) {
                final slide = Tween<Offset>(
                  begin: const Offset(
                    0.02,
                    0.0,
                  ), // Schuift heel subtiel 2% vanaf rechts binnen
                  end: Offset.zero,
                ).animate(animation);
                return SlideTransition(
                  position: slide,
                  child: FadeTransition(opacity: animation, child: child),
                );
              },
            ),
          ),
        ],
      ),
    );
  }

  double robotX = 0.0;
  double robotY = 0.0;
  double heading = 0.0;
  double turnRate = 0.0;
  final random = Random();
  bool mocking = false;
  void startMockTelemetry() {
    mocking = true;
    mocktimer?.cancel();
    mockbattery = 95;
    chargingstate = false;
    trail.clear();
    robotX = 0.0;
    robotY = 0.0;
    heading = 0.0;



    mocktimer = Timer.periodic(const Duration(milliseconds: 35), (timer) {

      turnRate += (random.nextDouble() - 0.5) * 0.05;

      packets++;
      if (random.nextDouble() < 0.01) {
        turnRate = (random.nextDouble() - 0.5) * 0.12;
      }

      turnRate *= 0.95;
      heading += turnRate;

      const double speed = 3.5;

      robotX += cos(heading) * speed;
      robotY += sin(heading) * speed;
      simTime += 0.05;

      simPitch = sin(simTime * 1.5) * 29.2 + (random.nextDouble() - 0.5) * 0.3;
      simRoll = cos(simTime * 2.0) * 29.8 + (random.nextDouble() - 0.5) * 0.3;
      simPitch *= 0.98;
      simRoll *= 0.98;
      if (random.nextDouble() < 0.03) {
        simPitch += (random.nextDouble() - 0.5) * 1.5;
        simRoll += (random.nextDouble() - 0.5) * 1.5;
      }
      _queueTelemetryUpdate(
        TelemetryData(
          yaw: heading,
          pitch: simPitch,
          roll: simRoll,
          xpos: robotX,
          ypos: robotY,
          batterylevel: mockbattery,
          occupiedslots: {1, 2},
          leftwheelport: 'A',
          rightwheelport: 'B',
          maxslots: '12',
          bytesperprogram: '512',
        ),
      );
    });
  }

  void _handleIncomingData(Uint8List bytes) {

    packets++;

    bleBuffer += utf8.decode(bytes, allowMalformed: true);
    final lines = bleBuffer.split('\n');
    bleBuffer = lines.removeLast();
    if (bleBuffer.length > 256) bleBuffer = '';

    for (final line in lines) {
      final trimmed = line.trim(); //[cite: 5]
      if (trimmed.isEmpty) continue;

      print("Line printed: $trimmed");
      final parts = line.trim().split(',');
      if (parts.length < 7) continue;
 
      final current = _pendingTelemetry ?? telemetry;
      final x = double.tryParse(parts[0]) ?? current.xpos;
      final y = double.tryParse(parts[1]) ?? current.ypos;
      final yawDeg = double.tryParse(parts[2]) ?? 0.0;
      final pitch = double.tryParse(parts[3]) ?? current.pitch;
      final roll = double.tryParse(parts[4]) ?? current.roll;
      final battery =
          (double.tryParse(parts[5])?.round() ?? current.batterylevel)
              .clamp(0, 100)
              .toInt();
      final occupied = <int>{};
      final mask = int.tryParse(parts[6]) ?? 0;
      for (int i = 0; i < 12; i++) {
        if ((mask & (1 << i)) != 0) {
        occupied.add(i);
          }
        }

      _queueTelemetryUpdate(
        TelemetryData(
          yaw: yawDeg * (pi / 180),
          pitch: pitch,
          roll: roll,
          xpos: x,
          ypos: y,
          batterylevel: battery,
          occupiedslots: occupied,
          leftwheelport: current.leftwheelport,
          rightwheelport: current.rightwheelport,
          maxslots: current.maxslots,
          bytesperprogram: current.bytesperprogram,
        ),
        
      );
      break;
    }
  }
}

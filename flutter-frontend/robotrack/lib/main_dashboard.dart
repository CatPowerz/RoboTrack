import 'package:flutter/material.dart';
import 'package:robotrack/classes/telemetrydata.dart';
import 'package:robotrack/widgets/visualisationwidget.dart';
import 'dart:async';
import 'dart:math';

import 'package:robotrack/widgets/visualisationyawpitchroll.dart';

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

  @override
  Widget build(BuildContext context) {
    List<Widget> pages = [
      Center(
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
                        FilledButton.icon(
                          onPressed: () {
                            setState(() {
                              selectedIndex = 1;
                            });
                          },

                          icon: Icon(Icons.question_mark, size: 24),
                          label: Text(
                            'How to install RoboTrack firmware',
                            style: TextStyle(
                              fontSize: 24,
                              fontFamily: 'Orbitron',
                            ),
                          ),
                        ),
                        const SizedBox(height: 24),
                      ],
                    ),
                  ),
                ),
                const SizedBox(height: 24),
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
                                            'The robot will drive around randomly like on any other mat.',
                                          ),
                                        ],
                                      ),
                                    ),
                                    actions: [
                                      FilledButton(
                                        onPressed: () {
                                          selectedIndex = 1;
                                          startMockTelemetry();
                                          Navigator.of(context).pop();
                                        },
                                        child: Icon(Icons.check),
                                      ),
                                      FilledButton(
                                        onPressed: () {
                                          Navigator.of(context).pop();
                                        },
                                        child: Icon(Icons.cancel),
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

      Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          Expanded(flex: 2, child: Image.asset('assets/rebornrobotrack.png')),
          Expanded(
            flex: 8,
            child: Row(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [
                Expanded(
                  flex: 6,
                  child: SizedBox.expand(
                    child: CustomPaint(
                      painter: FieldPainter(
                        xpos: telemetry.xpos,
                        ypos: telemetry.ypos,
                        yaw: telemetry.yaw,
                        pitch: telemetry.pitch,
                        roll: telemetry.roll,
                        camX: camX,
                        camY: camY,
                        trail: trail,
                      ),
                    ),
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.all(28.0),
                  child: Expanded(
                    flex: 4,
                    child: FractionallySizedBox(
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.center,
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          Center(
                            child: Row(
                              children: [
                                Card(
                                  child: Padding(
                                    padding: const EdgeInsets.all(8.0),
                                    child: SizedBox(
                                      width: 200,
                                      child: Text(
                                        'X: ${(telemetry.xpos / 10).toStringAsFixed(1)}',
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
                                      width: 200,
                                      child: Text(
                                        'Y: ${(telemetry.ypos / 10).toStringAsFixed(1)}',
                                        textAlign: TextAlign.center,
                                        style: TextStyle(fontSize: 48),
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
                                  'Yaw: ${normalizedYaw(telemetry.yaw).toStringAsFixed(1)}°',
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
                                  'Pitch: ${telemetry.pitch.round()}°',
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
                                  'Roll: ${telemetry.roll.round()}°',
                                  textAlign: TextAlign.center,
                                  style: TextStyle(fontSize: 48),
                                ),
                              ),
                            ),
                          ),
                          AttitudeVisualisation(
                            pitch: telemetry.pitch,
                            roll: telemetry.roll,
                            yaw: telemetry.yaw,
                            size: 100,
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
      const Placeholder(),
      const Placeholder(),
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
                  children: [
                    ...previousChildren,
                    if (currentChild != null) currentChild,
                  ],
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
                        NavigationRailDestination(
                          icon: Icon(Icons.settings_outlined),
                          label: Text('Settings'),
                          selectedIcon: Icon(Icons.settings),
                        ),
                      ],
                      selectedIndex: selectedIndex,
                      onDestinationSelected: (value) {
                        setState(() {
                          selectedIndex = value;
                        });
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
                child: pages[selectedIndex],
                key: ValueKey<int>(selectedIndex),
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

  @override
  void initState() {
    super.initState();
  }

  double robotX = 0.0;
  double robotY = 0.0;
  double heading = 0.0;
  double turnRate = 0.0;
  final random = Random();

  void startMockTelemetry() {
    mocktimer?.cancel();
    trail.clear();
    robotX = 0.0;
    robotY = 0.0;
    heading = 0.0;

    mocktimer = Timer.periodic(const Duration(milliseconds: 35), (timer) {
      turnRate += (random.nextDouble() - 0.5) * 0.05;

      if (random.nextDouble() < 0.01) {
        turnRate = (random.nextDouble() - 0.5) * 0.12;
      }

      turnRate *= 0.95;
      heading += turnRate;

      const double speed = 3.5;

      robotX += cos(heading) * speed;
      robotY += sin(heading) * speed;
      simTime += 0.05;
      simPitch = sin(simTime * 1.5) * 2.2 + (random.nextDouble() - 0.5) * 0.3;
      simRoll = cos(simTime * 2.0) * 1.8 + (random.nextDouble() - 0.5) * 0.3;
      simPitch *= 0.98;
      simRoll *= 0.98;

      if (random.nextDouble() < 0.01) {
        simPitch += (random.nextDouble() - 0.5) * 1.5;
        simRoll += (random.nextDouble() - 0.5) * 1.5;
      }
      setState(() {
        telemetry = TelemetryData(
          yaw: heading,
          pitch: simPitch,
          roll: simRoll,
          xpos: robotX,
          ypos: robotY,
          batterylevel: 95,
          occupiedslots: {1, 2},
          leftwheelport: 'A',
          rightwheelport: 'B',
          maxslots: '12',
          bytesperprogram: '512',
        );

        trail.add(Offset(robotX, robotY));
        if (trail.length > 250) {
          trail.removeAt(0);
        }

        camX += (robotX - camX) * 0.1;
        camY += (robotY - camY) * 0.1;
      });
    });
  }
}

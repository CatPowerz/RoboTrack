import 'package:flutter/material.dart';
import 'package:robotrack/classes/telemetrydata.dart';
import 'package:robotrack/pages/analytics_page.dart';
import 'dart:async';
import 'dart:math';

class MainDashboard extends StatefulWidget {
  const MainDashboard({super.key});

  @override
  State<MainDashboard> createState() => _MainDashboardState();
}

class _MainDashboardState extends State<MainDashboard> {
  int selectedIndex = 0;
  double camX = 0.0;
  double camY = 0.0;
  Timer? mocktimer;
  double mockangle = 0.0;
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
                              selectedIndex = 1;
                              startMockTelemetry();
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
      AspectRatio(
        aspectRatio: 2 / 1, // Bijv. 2:1 verhouding voor een robotica-mat
        child: CustomPaint(
          painter: FieldPainter(
            xpos: telemetry.xpos,
            ypos: telemetry.ypos,
            yaw: telemetry
                .yaw, // Als je firmware graden stuurt: telemetry.yaw * (pi / 180)
            camX: camX,
            camY: camY,
            trail: trail,
          ),
        ),
      ),
      const Placeholder(),
      const Placeholder(),
    ];
    return Scaffold(
      backgroundColor: Colors.transparent,
      body: Row(
        children: [
          if (selectedIndex != 0)
            NavigationRail(
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
          Expanded(
            child: IndexedStack(index: selectedIndex, children: pages),
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

    mocktimer = Timer.periodic(const Duration(milliseconds: 33), (timer) {
      turnRate += (random.nextDouble() - 0.5) * 0.02;

      if (random.nextDouble() < 0.01) {
        turnRate = (random.nextDouble() - 0.5) * 0.12;
      }

      turnRate *= 0.95;
      heading += turnRate;

      const double speed = 3.5;

      robotX += cos(heading) * speed;
      robotY += sin(heading) * speed;

      final double simPitch = (random.nextDouble() - 0.5) * 2.0;
      final double simRoll = (random.nextDouble() - 0.5) * 2.0;

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

        // Vloeiende camera tracking (LERP)
        camX += (robotX - camX) * 0.1;
        camY += (robotY - camY) * 0.1;
      });
    });
  }
}

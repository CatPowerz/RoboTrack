import 'package:flutter/material.dart';

class MainDashboard extends StatefulWidget {
  const MainDashboard({super.key});

  @override
  State<MainDashboard> createState() => _MainDashboardState();
}

class _MainDashboardState extends State<MainDashboard> {
  int selectedIndex = 0;
  final List<Widget> pages = [
    Center(
      child: Card(
        child: FractionallySizedBox(
          widthFactor: 0.5,
          heightFactor: 0.5,
          child: Column(
            children: [
              const SizedBox(height: 24),
              FractionallySizedBox(
                widthFactor: 0.8,

                child: Image.asset('assets/rebornrobotrack.png'),
              ),
              const Text('hoi'),
            ],
          ),
        ),
      ),
    ),
    const Placeholder(),
    const Placeholder(),
    const Placeholder(),
  ];
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.transparent,
      body: Row(
        children: [
          if (selectedIndex == 0)
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
}

import 'package:flutter/material.dart';
import 'package:robotrack/main_dashboard.dart';

void main() {
  runApp(const RoboTrack());
}

class RoboTrack extends StatelessWidget {
  
  const RoboTrack({super.key});

  
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'RoboTrack',
      debugShowCheckedModeBanner: false,
      themeMode: ThemeMode.dark,
      darkTheme: ThemeData(

        brightness: Brightness.dark,

        useMaterial3: true,

        colorSchemeSeed: Colors.tealAccent,
        scaffoldBackgroundColor: Colors.black,
        cardTheme: CardThemeData(
          color: const Color(0xFF1E222B),
          elevation: 4,

          shape: RoundedRectangleBorder(
            borderRadius: const BorderRadius.all(Radius.circular(12)),
            side: BorderSide(
              color: Colors.white.withValues(alpha: 0.8),
              width: 1,
            ),
          ),
        ),
      ),
      home: Stack(
        children: [
          Positioned.fill(
            child: Image.asset(
              'assets/bg-felix-mittermeier.jpg',
              width: double.infinity,
              height: double.infinity,
              fit: BoxFit.cover,
              color: Colors.black.withValues(alpha: 0.65), // Hoeveelheid zwart
              colorBlendMode: BlendMode.darken,
            ),
          ),
          //Positioned.fill(
          // child: Container(color: Colors.black.withValues(alpha: 0.7)),
          //  ),
          MainDashboard(),
        ],
      ),
    );
  }
}

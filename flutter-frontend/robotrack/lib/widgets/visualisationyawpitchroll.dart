import 'dart:math';

import 'package:flutter/material.dart';

class AttitudeVisualisation extends StatelessWidget {
  const AttitudeVisualisation({
    super.key,
    required this.pitch,
    required this.roll,
    required this.yaw,
    required this.size,
  });
  final double pitch;
  final double roll;
  final double yaw;
  final double size;
  @override
  Widget build(BuildContext context) {
    return Container(
      width: size,
      height: size,
      decoration: BoxDecoration(
        shape: BoxShape.rectangle,
        color: Colors.black.withValues(alpha: 0.7),
        border: Border.all(
          color: Colors.white.withValues(alpha: 0.5),
          width: 2.0,
        ),
        boxShadow: [
          BoxShadow(
            color: Colors.tealAccent.withValues(alpha: 0.2),
            blurRadius: 10,
            spreadRadius: 2,
          ),
        ],
      ),
      child: ClipRRect(
        child: Stack(
          alignment: Alignment.center,
          children: [
            Divider(color: Colors.white.withValues(alpha: 0.2), thickness: 1),
            VerticalDivider(
              color: Colors.white.withValues(alpha: 0.2),
              thickness: 1,
            ),
            Transform(
              alignment: Alignment.center,
              transform: Matrix4.identity()
                ..setEntry(3, 2, 0.002)
                ..rotateX((pitch * 5) * (pi / 180))
                ..rotateY((roll * 5) * (pi / 180))
                ..rotateZ(yaw * (pi / 180) * -1),
              child: Container(
                width: size * 0.6,
                height: size * 0.6,
                decoration: BoxDecoration(
                  color: Colors.tealAccent.withValues(alpha: 0.15),
                  borderRadius: BorderRadius.circular(8),
                  border: Border.all(color: Colors.tealAccent, width: 2),
                ),
                child: Icon(
                  Icons.arrow_upward,
                  color: Colors.tealAccent,
                  size: size / 2,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

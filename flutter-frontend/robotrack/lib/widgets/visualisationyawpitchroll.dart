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
            Transform.translate(
              offset: Offset(0, -pitch * 2.5),
              child: Transform(
                alignment: Alignment.center,
                transform: Matrix4.identity()
                  ..setEntry(3, 2, 0.002)
                  ..rotateX(pitch * (pi / 180))
                  ..rotateY(roll * (pi / 180))
                  ..rotateZ(yaw * (pi / 180)),
                child: Container(
                  width: size * 0.7,
                  height: 3,
                  decoration: BoxDecoration(
                    color: Colors.tealAccent,
                    borderRadius: BorderRadius.circular(2),
                    boxShadow: [
                      BoxShadow(
                        color: Colors.tealAccent.withValues(alpha: 0.8),
                        blurRadius: 8,
                      ),
                    ],
                  ),
                ),
              ),
            ),
            Container(
              width: 8,
              height: 8,
              decoration: BoxDecoration(
                shape: BoxShape.rectangle,
                color: Colors.white,
              ),
            ),
            Transform.rotate(
              angle: yaw * (pi / 180),
              child: Align(
                alignment: Alignment.topCenter,
                child: Padding(
                  padding: EdgeInsets.all(4),
                  child: Icon(Icons.navigation),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

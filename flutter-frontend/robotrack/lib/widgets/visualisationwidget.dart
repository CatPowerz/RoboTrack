import 'package:flutter/material.dart';
import 'dart:math';

class FieldPainter extends CustomPainter {
  final double xpos;
  final double ypos;
  final double yaw;
  final double camX;
  final double camY;
  final List<Offset> trail;
  FieldPainter({
    required this.xpos,
    required this.ypos,
    required this.yaw,
    required this.camX,
    required this.camY,
    required this.trail,
    required double pitch,
    required double roll,
  });

  void paint(Canvas canvas, Size size) {
    const double fieldwidth = 300.0;
    const double fieldheight = 300.0;
    final double scaleX = size.width / fieldwidth;
    final double scaleY = size.height / fieldheight;
    final double viewportSize = min(size.width, size.height);
    final double scale = viewportSize / fieldwidth;
    double currentviewX = 0;
    double currentviewY = 0;
    final double viewportLeft = 0.0;
    final double viewportTop = (size.height - viewportSize) / 2;
    final double centerX = viewportLeft + (viewportSize / 2);
    final double centerY = viewportTop + (viewportSize / 2);
    final double gridSize = 10.0 * scale;

    final double rawOffsetX = (centerX - (camX * scale)) % gridSize;
    final double offsetX = (rawOffsetX + gridSize) % gridSize;

    final double rawOffsetY = (centerY + (camY * scale)) % gridSize;
    final double offsetY = (rawOffsetY + gridSize) % gridSize;

    final viewportRect = Rect.fromLTWH(
      viewportLeft,
      viewportTop,
      viewportSize,
      viewportSize,
    );

    canvas.save();
    canvas.clipRect(viewportRect);
    final double drawx = centerX + ((xpos - camX) * scale);
    final double drawy = centerY - ((ypos - camY) * scale);
    final fieldPaint = Paint()
      ..color = const Color(0xFF1E222B)
      ..style = PaintingStyle.fill;
    final borderPaint = Paint()
      ..color = Colors.tealAccent.withValues(alpha: 0.5)
      ..style = PaintingStyle.stroke
      ..strokeWidth = 2.0;
    final double fieldDrawX = centerX + ((xpos - camX) * scale);
    final double fieldDrawY = centerY + ((ypos - camY) * scale);
    final gridPaint = Paint()
      ..color = Colors.white.withValues(alpha: 0.3)
      ..strokeWidth = 1.0;

    canvas.drawRect(viewportRect, fieldPaint);
    canvas.drawRect(viewportRect, borderPaint);
    for (
      double x = viewportRect.left + offsetX - gridSize;
      x <= viewportRect.right;
      x += gridSize
    ) {
      canvas.drawLine(
        Offset(x, viewportRect.top),
        Offset(x, viewportRect.bottom),
        gridPaint,
      );
    }

    for (
      double y = viewportRect.top + offsetY - gridSize;
      y <= viewportRect.bottom;
      y += gridSize
    ) {
      canvas.drawLine(
        Offset(viewportRect.left, y),
        Offset(viewportRect.right, y),
        gridPaint,
      );
    }
    final trailPaint = Paint()
      ..color = Colors.tealAccent.withValues(alpha: 0.6)
      ..strokeWidth = 2.0
      ..style = PaintingStyle.stroke
      ..strokeCap = StrokeCap.round;

    final path = Path();
    for (int i = 0; i < trail.length; i++) {
      final px = centerX + ((trail[i].dx - camX) * scale);
      final py = centerY - ((trail[i].dy - camY) * scale);
      if (i == 0) {
        path.moveTo(px, py);
      } else {
        path.lineTo(px, py);
      }
    }
    canvas.drawPath(path, trailPaint);
    canvas.save();
    canvas.translate(drawx, drawy);

    canvas.rotate(-yaw);

    final robotPaint = Paint()..color = Colors.tealAccent;
    //..style = PaintingStyle.fill;

    final robotPath = Path()
      ..moveTo(10, 0)
      ..lineTo(-15, -15)
      ..lineTo(-15, 15)
      ..close();

    canvas.drawPath(robotPath, robotPaint);
    //final headingPaint = Paint()
    //  ..color = Colors.white
    //  ..strokeWidth = 3;
    //canvas.drawLine(Offset.zero, const Offset(18, 0), headingPaint);

    canvas.restore();
    canvas.restore();
  }

  @override
  bool shouldRepaint(covariant FieldPainter oldDelegate) {
    return oldDelegate.xpos != xpos ||
        oldDelegate.ypos != ypos ||
        oldDelegate.yaw != yaw ||
        oldDelegate.camX != camX ||
        oldDelegate.camY != camY;
  }
}

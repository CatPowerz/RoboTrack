
class TelemetryData {
  final double yaw;
  final double pitch;
  final double roll;

  final double xpos;
  final double ypos;
  final int batterylevel;
  final Set<int> occupiedslots;

  final String leftwheelport;
  final String rightwheelport;
  final String maxslots;
  final String bytesperprogram;

  const TelemetryData({
    required this.yaw,
    required this.pitch,
    required this.roll,
    required this.xpos,
    required this.ypos,

    required this.batterylevel,
    required this.occupiedslots,
    required this.leftwheelport,
    required this.rightwheelport,
    required this.maxslots,
    required this.bytesperprogram,
  });
}

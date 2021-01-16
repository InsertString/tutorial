#include "main.h"

CVector StartingPosition(0,0);
CVector TargetPosition(0,0);
double starting_theta = 0;
double theta_target = 0;
double degrees_per_ms = 0;


void auto_drive_circle(double rad, double time, double end_theta, CVector center, int direction, int &step) {
  switch (step) {
    case 0 :
    StartingPosition = GlobalPosition;
    starting_theta = global_angle_d();
    startTimer(AUTO_CIRCLE_TIMER);
    degrees_per_ms = end_theta / time / 1000;
    step++;
    break;
    case 1 :
    theta_target = getTime(AUTO_CIRCLE_TIMER) * degrees_per_ms;

    if (direction == COUNTER) {
      TargetPosition.y = (rad * sin(theta_target / 180 * 3.14159)) + center.y;
      TargetPosition.x = (rad * cos(theta_target / 180 * 3.14159)) + center.x;

      drive_with_point(TargetPosition.y, TargetPosition.x, -theta_target);
    }
    else if (direction == CLOCK) {
      TargetPosition.y = (rad * sin(-theta_target / 180 * 3.14159)) + center.y;
      TargetPosition.x = (rad * cos(-theta_target / 180 * 3.14159)) + center.x;

      drive_with_point(TargetPosition.y, TargetPosition.x, theta_target);
    }

    if (getTime(AUTO_CIRCLE_TIMER) > (time * 1000)) {
      powerDrive(0, 0, 0);
      step++;
    }
    break;
  }
}

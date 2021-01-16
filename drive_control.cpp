#include "main.h"
#include "drive_control.hpp"

void powerDrive(double y, double x, double theta) {
  DriveLFF = y - theta - x;
  DriveLFB = -y + theta + x;
  DriveLBF = y - theta + x;
  DriveLBB = -y + theta - x;

  DriveRFF = -y - theta - x;
  DriveRFB = y + theta + x;
  DriveRBF = -y - theta + x;
  DriveRBB = y + theta - x;
}


PID yPID;
PID xPID;
PID thetaPID;

void drive_to_point(double targ_y, double targ_x, double targ_theta) {
  yPID.set_PID_constants(5, 0.1, 10);
  xPID.set_PID_constants(5, 0.1, 10);
  thetaPID.set_PID_constants(5, 0.1, 10);

  double local_target_y = (targ_y * (cos(global_angle))) + (targ_x * (sin(global_angle)));
  double local_target_x = (targ_x * (cos(global_angle))) + (-targ_y * (sin(global_angle)));

  yPID.set_PID_variables(local_target_y, 60, -60, 5);
  xPID.set_PID_variables(local_target_x, 60, -60, 5);


  thetaPID.set_PID_variables(targ_theta, 120, -120, 0);

  double y_power = 0;
  double x_power = 0;

  double x_curr = 0;
  double y_curr = 0;

  y_curr = (GlobalPosition.y * (cos(global_angle))) + (GlobalPosition.x * (sin(global_angle)));
  x_curr = (GlobalPosition.x * (cos(global_angle))) + (-GlobalPosition.y * (sin(global_angle)));

  y_power = yPID.output(y_curr);
  x_power = xPID.output(x_curr);

  powerDrive(y_power, x_power, thetaPID.output(global_angle_d()));

  //printf("%4.0f ltx, %4.0f cx || %4.0f lty, %4.0f cy \n", local_target_x, x_curr, local_target_y, y_curr);
}



void drive_with_point(double targ_y, double targ_x, double targ_theta) {
  yPID.set_PID_constants(20, 0.1, 10);
  xPID.set_PID_constants(20, 0.1, 10);
  thetaPID.set_PID_constants(5, 0.1, 10);

  double local_target_y = (targ_y * (cos(global_angle))) + (targ_x * (sin(global_angle)));
  double local_target_x = (targ_x * (cos(global_angle))) + (-targ_y * (sin(global_angle)));

  yPID.set_PID_variables(local_target_y, 50, -50, 5);
  xPID.set_PID_variables(local_target_x, 50, -50, 5);


  thetaPID.set_PID_variables(targ_theta, 120, -120, 0);

  double y_power = 0;
  double x_power = 0;

  double x_curr = 0;
  double y_curr = 0;

  y_curr = (GlobalPosition.y * (cos(global_angle))) + (GlobalPosition.x * (sin(global_angle)));
  x_curr = (GlobalPosition.x * (cos(global_angle))) + (-GlobalPosition.y * (sin(global_angle)));

  y_power = yPID.output(y_curr);
  x_power = xPID.output(x_curr);

  powerDrive(y_power, x_power, thetaPID.output(global_angle_d()));
}

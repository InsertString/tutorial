#include "main.h"

using namespace pros;

Controller master(E_CONTROLLER_MASTER);

// drive motors
Motor DriveLFF(1);
Motor DriveLFB(11);

Motor DriveLBF(3);
Motor DriveLBB(4);

Motor DriveRFF(6);
Motor DriveRFB(20);

Motor DriveRBF(9);
Motor DriveRBB(10);

// drive encoders
#define L_ENC_PORT1 1
#define L_ENC_PORT2 2
ADIEncoder LeftEncoder(L_ENC_PORT1, L_ENC_PORT2, true);
#define R_ENC_PORT1 7
#define R_ENC_PORT2 8
ADIEncoder RightEncoder(R_ENC_PORT1, R_ENC_PORT2, false);
#define B_ENC_PORT1 5
#define B_ENC_PORT2 6
ADIEncoder BackEncoder(B_ENC_PORT1, B_ENC_PORT2);

Imu gyro(12);

bool start_tracking = false;

void odom_task(void* param) {
	while (true) {
		CalculatePosition();
		//odomDebug();
	}
}

Task odom (odom_task, NULL, TASK_PRIORITY_DEFAULT-1, TASK_STACK_DEPTH_DEFAULT, "ODOM");

void initialize() {
	pros::lcd::initialize();
	gyro.reset();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {

	double x_t = 0;
	double y_t = 0;
	double angle = 0;
	bool start = false;
	int test_step = 0;
	CVector test_center(-50,0);

	while (true) {
		//printf("%4.0f raw, %4.0f func, %4.0f funcd, %4.0f glob\n", gyro.get_rotation(), gyro_value(), global_angle_d(), global_angle);

		if (master.get_digital(DIGITAL_A)) {
			drive_to_point(0, 20, 0);
		}
		else if (master.get_digital_new_press(DIGITAL_X)) {
			start = true;
			test_step = 0;
			//startTimer(TEST_TIMER);
		}
		else if (start == true) {
			auto_drive_circle(50, 1.75, 90, test_center, COUNTER, test_step);

			if (test_step == 2) start = false;
		}
	/*	else if (start == true && getTime(TEST_TIMER) < 2510) {
			angle = getTime(TEST_TIMER) / 10 * 0.36;
			x_t = 40 * (cos(angle / 180 * 3.14159));
			y_t = 40 * (sin(angle / 180 * 3.14159));

			drive_with_point(y_t, x_t, -angle);
		}*/
		else {
			powerDrive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_LEFT_X), master.get_analog(ANALOG_RIGHT_X));
		}

		/*
		if (master.get_digital(DIGITAL_A)) {
			drive_to_point(0, 0, 180);
		}
		else if (master.get_digital(DIGITAL_B)) {
			drive_to_point(0, 0, 0);
		}
		else if (master.get_digital(DIGITAL_Y)) {
			drive_to_point(0, 0, 270);
		}
		else {
			powerDrive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_LEFT_X), master.get_analog(ANALOG_RIGHT_X));
		}
		*/

		delay(20);
	}
}

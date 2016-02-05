#pragma config(Motor,  port1,           treadIntake,   tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftDrive2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftDrive1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           launcherLeft,  tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           launcherRight, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           rightDrive1,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightDrive2,   tmotorVex393_MC29, openLoop)
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

////////////////////////// SOFTWARE DEFINES ////////////////////////////////////

#define DRIVE_DZ 30 // The drive stick deadzone for both sticks

////////////////////////////////////////////////////////////////////////////////
/*
 * Deadzones a joystick input.
 *
 * @param stickValue The raw joystick value.
 * @param dz The lower threshold for input to go through.
 */
int applyDeadzone(int stickValue, int dz)
{
	int abValue = abs(stickValue);

	// If the absolute stick value is below the thresh return 0
	if (abValue < dz)
	{
		return 0;
	}
	else
	{
		return stickValue;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	// Used to keep track of the on state of the launch motors
	bool shootOn = true;

	// Turn on shoot motors initially
	motor[launcherLeft] = 127;
  motor[launcherRight] = 127;

	while (true)
	{
		// Run drive motors in tank drive
	  motor[leftDrive1] = applyDeadzone(vexRT[Ch3], DRIVE_DZ);
	  motor[leftDrive2] = applyDeadzone(vexRT[Ch3], DRIVE_DZ);
	  motor[rightDrive1] = applyDeadzone(vexRT[Ch2], DRIVE_DZ);
	  motor[rightDrive2] = applyDeadzone(vexRT[Ch2], DRIVE_DZ);

	  // Toggle button for the spin motors
	  if (time100[T1] > 3 && vexRT[Btn5U] == 1)
	  {
	  	// Reset the timer and toggle the on state of shoot motors
	  	clearTimer(T1);
	  	shootOn = !shootOn;

	  	// Set shoot motor speed respectively
	  	if (shootOn)
	  	{
	  		motor[launcherLeft] = 127;
	  		motor[launcherRight] = 127;
	  	}
	  	else
	  	{
	  		motor[launcherLeft] = 0;
	  		motor[launcherRight] = 0;
	  	}
	  }

	  // Press shoulder buttons to run ball belt
	  if (vexRT[Btn6U] == 1)
	  {
	  	motor[treadIntake] = 127;
	  }
	  else if (vexRT[Btn6D] == 1)
	  {
	  	motor[treadIntake] = -127;
	  }
	  else
	  {
	  	motor[treadIntake] = 0;
	  }
	}
}

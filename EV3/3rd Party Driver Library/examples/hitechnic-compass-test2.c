#pragma config(Motor,  motorB,          M_RIGHT,       tmotorNormal, PIDControl, reversed)
#pragma config(Motor,  motorC,          M_LEFT,        tmotorNormal, PIDControl, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * hitechnic-compass.h provides an API for the HiTechnic Compass Sensor.  This program
 * demonstrates how to use that API to calibrate the compass.
 *
 * The code here is made to work with the standard NXT Tribot.  You will need to edit
 * the WHEELDIST, WHEELSIZE and MOTORSPEED figures to make it work with your robot.
 *
 * Remeber that the robot shouldn't spin more than 360 degrees per 20 seconds.  Also
 * make sure it spins a bit more than 360, perhaps 1 and 1/4 or 1 and 1/2.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Added pulsating "*" to indicate progress
 * - 0.3: More comments
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 25 November 2009
 * version 0.3
 */

#include "hitechnic-compass.h"

// These measurements are in milimeters.
#define WHEELDIST 115  // distance between the wheels
#define WHEELSIZE 56   // diameter of the wheels

#define MOTORSPEED 4   // speed at which motors should turn

// Struct to hold sensor data
tHTMC compass;

// Lets you know when 20 seconds is over, can help with setting up
// the initial timing and motor speed.
task timeMe() {
  sleep(20000);
  playSound(soundBeepBeep);
  while(bSoundActive) sleep(1);
}

// Pulse a big "*" at the bottom of the screen to show that it's
// doing something.
task showPulse() {
  while (true) {
    displayCenteredBigTextLine(6, " ");
    sleep(400);
    displayCenteredBigTextLine(6, "*");
    sleep(400);
  }
}

// Does some voodoo maths to calculate how many times the wheels should rotate
// to make the robot spin about 360 degrees.
short numRotations() {
  return ((WHEELDIST * 3142) / 1000) / ((WHEELSIZE * 3142) / 1000);
}

// Start the calibration and complain loudly if something goes wrong
void startCalibration() {
  if (!sensorCalibrate(&compass)) {
    eraseDisplay();
    displayTextLine(1, "ERROR: Couldn't");
    displayTextLine(2, "calibrate sensor.");
    displayTextLine(4, "Check connection");
    displayTextLine(5, "and try again.");
    playSound(soundException);
    while(bSoundActive) sleep(1);
    sleep(5000);
    stopAllTasks();
  }
}

// Stop the calibration and complain loudly if somethign goes wrong
void stopCalibration() {
  if (!sensorStopCalibrate(&compass)) {
    eraseDisplay();
    displayTextLine(1, "ERROR: Calibration");
    displayTextLine(2, "has failed.");
    displayTextLine(4, "Check connection");
    displayTextLine(5, "and try again.");
    playSound(soundException);
    while(bSoundActive) sleep(1);
    sleep(5000);
    stopAllTasks();
  } else {
    displayTextLine(1, "SUCCESS: ");
    displayTextLine(2, "Calibr. done.");
    playSound(soundUpwardTones);
    while(bSoundActive) sleep(1);
    sleep(5000);
  }
}

task main () {
  bFloatDuringInactiveMotorPWM = true;
  short numDegrees = 0;
  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "Compass");
  displayCenteredTextLine(3, "Test 2");

  // Initialise and configure struct and port
  initSensor(&compass, S1);

  nMotorEncoder[M_RIGHT] = 0;
  nMotorEncoder[M_LEFT] = 0;
  // This will make the robot spin about 1.5 times, depends on many factors, YYMV, etc
  numDegrees = ((numRotations() * 3) / 2) * 450;
  startTask(timeMe);
  startCalibration();
  displayCenteredTextLine(5, "Calibrating...");
  startTask(showPulse);
  motor[M_RIGHT] = MOTORSPEED;
  motor[M_LEFT] = -MOTORSPEED;

  while(nMotorEncoder[M_RIGHT] < numDegrees) sleep(5);
  motor[M_LEFT] = 0;
  motor[M_RIGHT]= 0;
  stopCalibration();
  displayCenteredTextLine(5, "Calibration done");
  sleep(5000);
}

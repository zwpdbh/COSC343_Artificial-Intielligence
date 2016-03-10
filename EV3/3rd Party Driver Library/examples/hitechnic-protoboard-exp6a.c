#pragma config(Sensor, S1,     HTPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * hitechnic-protoboard.h provides an API for the HiTechnic Protoboard.  This is program 6a
 * for the HTPB experimenter's kit.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 07 May 2010
 * version 0.1
 */

#include "hitechnic-protoboard.h"

task main() {
  // The data to be written: 0x30 = 110000 binary,
  // makes B4,B5 digital ports outputs.
  HTPBsetupIO(HTPB, 0x30);

  while(true) {

    // Turn off the LED
    HTPBwriteIO(HTPB, 0x00);

    eraseDisplay();
    displayTextLine(2, "running");

    // Wait a random time between 5 and 10 seconds.
    sleep(random(5000) + 5000);

    // Switch on the LED and reset the timer
    HTPBwriteIO(HTPB, 0x10);
    time1[T1] = 0;

    // Wait for user to press the stop button
    while (HTPBreadIO(HTPB, 0xF3) != 0x01) {
      sleep(5);
    }

    eraseDisplay();
    displayTextLine(2, "%d", time1[T1]);

    // Wait for user to reset
    while (HTPBreadIO(HTPB, 0xF3) != 0x03) {
      sleep(5);
    }
  }
}

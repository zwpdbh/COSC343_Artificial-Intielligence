#pragma config(Sensor, S1,     HTPB,                sensorI2CCustom9V)
#pragma config(Sensor, S2,     SOUND_PORT,          sensorAnalogInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * hitechnic-protoboard.h provides an API for the HiTechnic Protoboard.  This is program 3
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
  // Local variables
  short soundlevel;
  ubyte outputdata;

  // The data to be written: 0x3F = 111111 binary,
  // makes all digital ports outputs.
  HTPBsetupIO(HTPB, 0x3F);

  while(true) {
    // Get the value from the LEGO sound sensor.
    soundlevel = 1023 - SensorValue[SOUND_PORT];

    eraseDisplay();
    displayTextLine(1, "%d", soundlevel);

    // Depending on the input voltage on A0,
    // turn on the corresponding LED.
    outputdata = 0x01;
    outputdata = 0x01;
    if (soundlevel >  65) outputdata = 0x02;
    if (soundlevel > 108) outputdata = 0x04;
    if (soundlevel > 180) outputdata = 0x08;
    if (soundlevel > 300) outputdata = 0x10;
    if (soundlevel > 500) outputdata = 0x20;

    HTPBwriteIO(HTPB, outputdata);
    sleep(50);
  }
}

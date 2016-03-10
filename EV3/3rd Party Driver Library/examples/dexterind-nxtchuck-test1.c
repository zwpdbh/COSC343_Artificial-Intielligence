#pragma config(Sensor, S1,     CHUCKNORRIS,    sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * dexterind-nxtchuck.h provides an API for the Dexter Industries NXTChuck sensor.
 * This program demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Matthew Richardson and Dexter Industries for providing me with the
 * hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 31 October 2012
 * version 0.1
 */

#include "dexterind-nxtchuck.h"

task main()
{

  tNunchuck chucky;

  byte Device = 0;
  NXTChuckreadIdent(CHUCKNORRIS, chucky);
  writeDebugStreamLine("dev: %d", Device);

  while (true)
  {
    //if(Device == NXTCHUCK_DEVICE_NUNCHUK){                                          // If it identified the extension as a Nunchuk
      if (NXTChuckreadSensor(S1, chucky)) {      // Read the Nunchuk

        displayTextLine(0, "Stick  X  %d", chucky.stickX);
        displayTextLine(1, "Stick  Y  %d", chucky.stickY);
        displayTextLine(2, "Accel  X  %d", chucky.accelX);
        displayTextLine(3, "Accel  Y  %d", chucky.accelY);
        displayTextLine(4, "Accel  Z  %d", chucky.accelZ);
        displayTextLine(5, "Button C  %d", chucky.buttonC);
        displayTextLine(6, "Button Z  %d", chucky.buttonZ);
        displayTextLine(7, "Buttons   %d", chucky.buttons);
      }
      else {
        sleep(100);
        eraseDisplay();
        displayTextLine(0, "Failed");
      }
    //}
    sleep(10);
  }
}

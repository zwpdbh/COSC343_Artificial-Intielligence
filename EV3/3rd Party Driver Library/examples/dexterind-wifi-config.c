#pragma config(Sensor, S1,     COLOUR,              sensorColorNxtNONE)
#pragma config(Sensor, S3,     DTMP,                sensorAnalogInactive)
#pragma config(Motor,  motorA,          M1,            tmotorNormal, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#define __RS485_DEBUG__ 1

#include "common.h"
#include "dexterind-wifi.h"

void configureWiFi(char *_ssid, char *_key)
{
  short len;
  RS485clearRead();      // Clear out the buffer and test TX/RX.
  sleep(1000);          // Must be run first!
  DWIFIsetEcho(false);     // Must be run first!
  sleep(1000);          // Must be run first!
  RS485clearRead();
  eraseDisplay();
  DWIFIsetSWControl();  // Must be run first!
  RS485clearRead();
  DWIFIsetVerbose(false);
  sleep(100);
  RS485clearRead();
  RS485read(RS485rxbuffer, len);
  DWIFIsetSSID(_ssid);
  DWIFIsetDHCP(true);
  DWIFIsetWPAPSK(_ssid, _key);
  sleep(20000);
  DWIFIsaveConfig();
}

task main()
{
  char *ssid = "YOURSSID";
  char *wpa_psk = "YOURPASSWORD";

  writeDebugStreamLine("ssid: %s", ssid);
  writeDebugStreamLine("psk: %s", wpa_psk);
  short len;
  eraseDisplay();
  bNxtLCDStatusDisplay = true; // Enable top status line display
  writeDebugStream("Scanning for wifi sensor: ");

  // You can play with these to see if they work for you.
  // I tend to use the 460800 rate as it's the fastest speed
  // that I can use reliably.
  //DWIFIsetBAUDRate(9600);
  DWIFIsetBAUDRate(230400);
  DWIFIresetConfig();
  playSound(soundBlip);
  while(nNxtButtonPressed != kEnterButton) sleep(1);
  DWIFIsetBAUDRate(230400);

  configureWiFi((char *)ssid, (char *)wpa_psk);
  // set_verbose(false);
  // Receive();
  sleep(100);
  while(true)
  {
    RS485read(RS485rxbuffer, len, 100);
  }
  playSound(soundBeepBeep);
}

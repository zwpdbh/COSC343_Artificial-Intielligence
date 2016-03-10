#pragma config(Sensor, S2,     ,               sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     ,               sensorEV3_GenericI2C)
#pragma config(Sensor, S4,     ,               sensorEV3_GenericI2C)
#pragma config(MotorPidSetting,  motorA,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
#pragma config(MotorPidSetting,  motorB,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
#pragma config(MotorPidSetting,  motorC,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
#pragma config(MotorPidSetting,  motorD,  255, 255, 65535, 255, 255,   65535, 65535, 65535)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//////////////////////////////////////////////////////////////////////////////////////////
//
//                           I2C Coding Source Code Examples
//                           ===============================
//
// Contains code snippets for working with the Legacy NXT I2C sensors on a EV3 brick.
//
////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
//
//                waitForI2CReply(TSensors nPortIndex, const int nReplyLength)
//
// Function will delay waiting for last I2C transaction to finish.
//
//////////////////////////////////////////////////////////////////////////////////////////

bool waitForI2CReply(tSensors nPortIndex)
{
	while (nI2CStatus[nPortIndex] == i2cStatusPending)
		wait1Msec(1);

	//if (nI2CBytesReady[nPortIndex] != nReplyLength)
	//	return false;

	return true;
}


//
// Alternate version showing more complicated error checking
//

bool checkErrorStatus(tSensors nPortIndex, const int nReplyLength)
{
	while (nI2CStatus[nPortIndex] == i2cStatusPending)
		wait1Msec(1); // Waiting for I2C transaction to complete

	//
	// Handle all possible return status. You may want to customize the
	// code for your particular situation.
	//
	switch (nI2CStatus[nPortIndex])
	{
	case i2cStatusNoError:
		return true;

	case i2cStatusPending:
		// Shouldn't reach here because of preceding 'while' clause
		return false;

	case i2cStatusBadConfig:
		// Sensor is not configured for I2C messaging.
		return false;

	case i2cStatusFailed:
		// re-initialize sensor. An I2C messaging error occurred.
		return false;

	default:
		// "Illegal" value
		return false;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//                           Read from an I2C Device
//
// Sends a message to I2C sensor to read data from the device. You'll have to poll the
// status of the I2C communications channel to tell when the 'read' is complete.
//
//////////////////////////////////////////////////////////////////////////////////////////

bool sendSensorRead(tSensors nPortIndex, const ubyte &nSendMsg, const int nReplyLength)
{
	TI2CStatus nStatus;

	if (nI2CStatus[nPortIndex] == i2cStatusPending)
		return false;   // Can't send message to a busy device

	nStatus = sendI2CMsg(nPortIndex, &nSendMsg, nReplyLength);
	return (nStatus == i2cStatusNoError);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//                        readI2CReply(TSensors nPortIndex)
//
// Collects the reply bytes from an I2C message.
//
//////////////////////////////////////////////////////////////////////////////////////////

bool readSensorReply(tSensors nPortIndex, ubyte *pReplyMsg, const int nReplyLength)
{
	TI2CStatus nStatus;

	if (!waitForI2CReply(nPortIndex))
	{
	  memset(pReplyMsg, 0, nReplyLength);
	  return false;
	}

	nStatus = readI2CReply(nPortIndex, pReplyMsg, nReplyLength);
	return (nStatus == i2cStatusNoError);
}


////////////////////////////////////////////////////////////////////////////////////////////
//
//          Sample Task to Continuously read the sensor characteristics
//
////////////////////////////////////////////////////////////////////////////////////////////

int nMsgCountGood = 0;
int nMsgCountTimeout = 0;

task main()
{
	const tSensors sensorPort = S2;
	const int kI2CAddress    = 0x02;    // You may want to make this a function parameter
	const int kRegisterIndex = 0x00;    // You may want to make this a function parameter

	static const ubyte nReadDeviceID[] =
	{
		2,                   // This is length field for transmitted message.
		kI2CAddress,         // The I2C address of the device. Almost all devices use value '0x02'
		kRegisterIndex,      // The internal register index within the sensor to start writing at.
	};

	const int kReplyLength = 8;         // You might want to make this a function parameter.
	static ubyte nReplyBytes[kReplyLength];

  clearDebugStream();

  while ((nMsgCountGood + nMsgCountTimeout) < 1000)
  {
    clearTimer(T1);
    sendSensorRead(sensorPort, nReadDeviceID[0], kReplyLength);
    while (true)
    {
    	if ((nI2CStatus[sensorPort] == i2cStatusPending) || (nI2CStatus[sensorPort] == i2cStatusStartTransfer))
    	{
    		if (time1[timer1] > 48)
	    	{
	    		++nMsgCountTimeout;
	    		break;
	    	}
    	}
    	else if (nI2CStatus[sensorPort] == i2cStatusNoError)
    	{
    		readSensorReply(sensorPort, &nReplyBytes[0], kReplyLength);
    		++nMsgCountGood;
    		break;
    	}
    	else
    	{
  			++nMsgCountTimeout;
    		break;
    	}
    }
  }
  writeDebugStreamLine("Total: %d", nMsgCountGood + nMsgCountTimeout);
  writeDebugStreamLine("Good: %d", nMsgCountGood);
  writeDebugStreamLine("Tout: %d", nMsgCountTimeout);
}

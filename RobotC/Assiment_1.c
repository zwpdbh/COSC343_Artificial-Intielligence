#pragma config(Sensor, S1,     leftBumper,     sensorEV3_Touch)
#pragma config(Sensor, S2,     rightBumper,    sensorEV3_Touch)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
task MovingForward();

//task ReflectionChanged();

/**Self Defined function*/
//void sideAction() {
//	displayTextLine(3, "Left: %i", getMotorSpeed(leftMotor));
//	displayTextLine(4, "Right: %i", getMotorSpeed(rightMotor));
//	stopTask(MovingForward);
//	if (getTouchValue(leftBumper) == 1) {
//		setMotorSpeed(leftMotor, -20);
//		setMotorSpeed(rightMotor, -20);
//		wait1Msec(1000);
//
//		resetMotorEncoder(leftMotor);
//		while(getMotorEncoder(leftMotor)<=360) {
//			setMotorSyncEncoder(leftMotor, rightMotor, -100, 360, -30);
//		}
//	} else if (getTouchValue(rightBumper) == 1) {
//		setMotorSyncEncoder(leftMotor, rightMotor, 0, 360, -30);
//		setMotorSyncEncoder(leftMotor, rightMotor, 100, 360, -30);
//	}
//	startTask(MovingForward);
//}



task main()
{
  int maxColor = getColorReflected(colorSensor);
  int minColor = getColorReflected(colorSensor);
	int previousColor = getColorReflected(colorSensor);
	int count = 0; // count the number of tile run over

	// Begin to move!
	startTask(MovingForward);

	//while(true) {
	//	if (getTouchValue(leftBumper) == 1 || getTouchValue(rightBumper) == 1) {
	//		sideAction();
	//	}
	//}

	// moving until the colorSensor detect 10 tiles
	while(count<=10) {
		// Use Sensor to get Color
		 displayTextLine(2, "Count: %d", count);
		 int currentColor = getColorReflected(colorSensor);
		 displayTextLine(4, "currentColor: %d", currentColor);

		 displayTextLine(8, "maxColor: %d", maxColor);
		 displayTextLine(7, "minColor: %d", minColor);

		 int colorChange = abs(currentColor - previousColor);
		 displayTextLine(5, "colorChanged: %d", colorChange);

		 if (currentColor > maxColor) {
		   	maxColor = currentColor;
		 } else if (currentColor < minColor) {
		 	 minColor = currentColor;
		 }

		 // if the color different is bigger than 20
		 if (abs(currentColor - previousColor)>30) {
		 		previousColor = currentColor;
		 		if (currentColor < 40) {
		 				count++;
		 				playSound(soundBlip);
		 		}

		 }

		 if (SensorValue(leftBumper) == 1) {break;}
	}

	// After moving 15 tiles, stop!
	stopTask(MovingForward);
} // END of main()


/**Moving Class*/
task MovingForward() {
	setMotorSync(leftMotor, rightMotor, 0, 30);
}



//task MovingBackward() {
//	stopTask(MovingForward);
//	setMotorSync(leftMotor, rightMotor, 0, -30);
//	setMotorSpeed(leftMotor, -30);
//	setMotorSpeed(rightMotor, -30);
//}




///**Sensor Color Class*/
//task ReflectionChanged() {
//  int maxColor = 0;
//  int minColor = 100;
//  int currentColor = 0;
//  int previousColor = 0;

//	currentColor = getColorReflected(colorSensor);
//	displayTextLine(2, "Reflection: %d", currentColor);

//	if (currentColor > maxColor) {
//		maxColor = currentColor;
//	}
//	if (currentColor < minColor) {
//		minColor = currentColor;
//	}


//}

#pragma config(Motor,  motorA,          LEFT,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          RIGHT,         tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// sync motor test
task main()
{
	setMotorSyncTime(LEFT, RIGHT, 0, 2000, 50);
	sleep(3000);
}

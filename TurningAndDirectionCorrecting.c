#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in4,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  leftTouch,      sensorSONAR_cm)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  rightIME,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftIME,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           rightMotor,    tmotorVex269_MC29, PIDControl, driveRight, encoderPort, I2C_1)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex269_MC29, PIDControl, reversed, driveLeft, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Steven Killoran

void adjustCourse();
void leftTurn();
void rightTurn();

task main(){
	bool run = true;
	int turns = 0;
	while (run){
		adjustCourse(); // this keeps the left wheel from making the whole swerveBot drift left

		motor[rightMotor] = 124;// the main controller for driving forwards
		motor[leftMotor] = 124;
		
		//testing out the turns
		if(SensorValue[sonarSensor] < 45 && turns <2){

			if(!turns == 1){
				leftTurn();
				turns++;
			}
			else{
				leftTurn();
				turns++;
			}
		}

		if(SensorValue[sonarSensor] < 45 && turns ==2){
			rightTurn();
			turns++;
		}
	}

}

void adjustCourse(){
	//The left wheel is slower or the bot is more heavy on one side. This tells it to speed up if it drifts to one side.
	int a = 0;
	a = SensorValue[gyro];
	motor[rightMotor] = 124;
	motor[leftMotor] = 124;
	wait10Msec(1);
	if(SensorValue[gyro] < a){
		motor[rightMotor] = 124;
		motor[leftMotor] = 126;
		wait10Msec(2);
	}
	
	//add an else to check if gyro >a with motors speeds swapped if i need to check this again in the future.
	//this would then stop drifting to the right as well.

}

void leftTurn(){
	//~90 degree left turns,
	int a = 0;
	a = SensorValue[gyro];

	//crude motor control
			//This quickly turns the robot until the gyro sensor reports a value between -80 and -89 degrees as we cant stop it perfectly at 90.
			//The different numbers betweent he right and left motors are due to the actual robot having a wheel that doesnt rotate as fast.
	motor[rightMotor] = 103;
	motor[leftMotor] = -104;
	//a number more positive than -890 or -800
	waitUntil(SensorValue[gyro] >= a - 890 && SensorValue[gyro] <= a - 800);

	//fine motor control
			//This slowly adjusts the turn to as close to 90 degrees
			//The different numbers betweent he right and left motors are due to the actual robot having a wheel that doesnt rotate as fast.
	motor[rightMotor] = 25;
	motor[leftMotor] = 20;
	waitUntil(SensorValue[gyro] <= a - 895 && SensorValue[gyro] >= a - 905);

}

void rightTurn(){
	//~90 degree right turns,
	int a =0;
	a = SensorValue[gyro]; //gyro -1921

	//crude motor control
			//This quickly turns the robot until the gyro sensor reports a value between -80 and -89 degrees as we cant stop it perfectly at 90.
			//The different numbers betweent he right and left motors are due to the actual robot having a wheel that doesnt rotate as fast.
	motor[rightMotor] = -124;
	motor[leftMotor] = 127;				//-1121													-1024
	waitUntil(SensorValue[gyro] >= a + 800 && SensorValue[gyro] <= a + 897);

	//fine motor control
			//This slowly adjusts the turn to as close to 90 degrees
			//The different numbers betweent he right and left motors are due to the actual robot having a wheel that doesnt rotate as fast.
	motor[rightMotor] = 25;
	motor[leftMotor] = 20;
	waitUntil(SensorValue[gyro] >= a + 890 && SensorValue[gyro] <= a + 910);

}

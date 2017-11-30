#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    mgmp,           sensorPotentiometer)
#pragma config(Sensor, dgtl1,  ldt,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rdt,            sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  data,           sensorDigitalOut)
#pragma config(Sensor, dgtl10, clock,          sensorDigitalOut)
#pragma config(Sensor, I2C_1,  towerEnc,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  elbowEnc,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           claw,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           elbow,         tmotorVex393_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port3,           tower,         tmotorVex393_MC29, PIDControl, encoderPort, I2C_1)
#pragma config(Motor,  port4,           bldt,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           brdt,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           fldt,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           frdt,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mgml,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           mgmr,          tmotorVex393_MC29, openLoop)
#pragma config(MotorPidSetting,  port2,  50, 50, 1000, 4, 10,   33, 45, 60)
#pragma config(MotorPidSetting,  port3,  50, 50, 1000, 4, 10,   33, 45, 60)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
    Copyright (C) 2017 Quantum Robotics

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#pragma platform(VEX2)
#include "Vex_Competition_Includes.c"
#include "driving.c"
#include "auton.c"
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

void waitForRelease()
{
	while(nLCDButtons != 0)
		wait1Msec(5);
}
void waitForPress()
{
	while(nLCDButtons == 0)
		wait1Msec(5);
}
void pre_auton(){//Selects auton program
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true;
	SensorType[gyro] = sensorNone;
	wait1Msec(1500);
	SensorType[gyro] = sensorGyro;
	playTone(440,10);
	wait1Msec(100);
	playTone(660,10);
	/*
	while(nLCDButtons != centerButton){
		switch(count){
		case 0:
			displayLCDCenteredString(0, "Autonomous 1");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				count++;
			}
		break;
		case 1:
			displayLCDCenteredString(0, "Autonomous 2");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				count++;
			}
			break;
		case 2:
			displayLCDCenteredString(0, "Autonomous 3");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				count++;
			}
			break;
		case 3:
			displayLCDCenteredString(0, "Autonomous 4");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 0;
			}
			break;
		default:
			count = 0;
			break;

		}
	}*/
}
task autonomous(){
	startTask(auton);
}
task usercontrol(){
	startTask(drive);
}

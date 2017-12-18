#pragma config(Sensor,in1,fourbarPot,sensorPotentiometer)
#pragma config(Sensor,dgtl1,ldtEnc,sensorQuadEncoder)
#pragma config(Sensor,dgtl3,rdtEnc,sensorQuadEncoder)
#pragma config(Sensor,dgtl5,mgmEnc,sensorQuadEncoder)
#pragma config(Sensor,dgtl7,ldr4bEnc,sensorQuadEncoder)
#pragma config(Sensor,dgtl9,rdr4bEnc,sensorQuadEncoder)
#pragma config(Motor,port1,mgmr,tmotorVex393_HBridge,openLoop)
#pragma config(Motor,port2,fourbar,tmotorVex393_MC29,openLoop)
#pragma config(Motor,port3,ldr4b,tmotorVex393_MC29,PIDControl,encoderPort,dgtl7)
#pragma config(Motor,port4,ldt1,tmotorVex393_MC29,PIDControl,encoderPort,dgtl1)
#pragma config(Motor,port5,ldt2,tmotorVex393_MC29,PIDControl,encoderPort,dgtl1)
#pragma config(Motor,port6,rdt1,tmotorVex393_MC29,PIDControl,encoderPort,dgtl3)
#pragma config(Motor,port7,rdt2,tmotorVex393_MC29,PIDControl,encoderPort,dgtl3)
#pragma config(Motor,port8,rdr4b,tmotorVex393_MC29,PIDControl,encoderPort,dgtl9)
#pragma config(Motor,port9,claw,tmotorVex393_MC29,openLoop)
#pragma config(Motor,port10,mgml,tmotorVex393_HBridge,openLoop)
#pragma config(MotorPidSetting,port3,50,90,1000,3,10,33,45,60)
#pragma config(MotorPidSetting,port4,50,90,1000,3,10,33,45,60)
#pragma config(MotorPidSetting,port5,50,90,1000,3,10,33,45,60)
#pragma config(MotorPidSetting,port6,50,90,1000,3,10,33,45,60)
#pragma config(MotorPidSetting,port7,50,90,1000,3,10,33,45,60)
#pragma config(MotorPidSetting,port8,50,90,1000,3,10,33,45,60)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#pragma platform(VEX2)
//#pragma config(Sensor, dgtl9, data, sensorDigitalOut)
//#pragma config(Sensor, dgtl10, clock, sensorDigitalOut)
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
#include "config.c"
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
	/*
	SensorType[gyro] = sensorNone;
	wait1Msec(1500);
	SensorType[gyro] = sensorGyro;
	*/
	playTone(440,10);
	wait1Msec(100);
	playTone(660,10);
	//setStripColor(120, 31, 0, 0, 255);

	while(nLCDButtons != centerButton){
		switch(lcdCount){
		case 0:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, "Left Side MGM");
			displayLCDString(1,0, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				lcdCount = 3;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				lcdCount++;
			}
		break;
		case 1:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, "Right Side MGM");
			displayLCDString(1,0, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				lcdCount--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				lcdCount++;
			}
			break;
		case 2:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, "Autonomous 3");
			displayLCDString(1,0, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				lcdCount--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				lcdCount++;
			}
			break;
		case 3:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, "Autonomous 4");
			displayLCDString(1,0, "<         Enter        >");
			waitForPress();
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				lcdCount--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				lcdCount = 0;
			}
			break;
		default:
			lcdCount = 0;
			break;

		}
	}
}
task autonomous(){
	startTask(auton);
}
task usercontrol(){
	startTask(drive);
}

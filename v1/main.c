#pragma config(Sensor, in1,    potLeftTower,   sensorPotentiometer)
#pragma config(Sensor, in2,    potRightTower,  sensorPotentiometer)
#pragma config(Sensor, in4,    potLeftClaw,    sensorPotentiometer)
#pragma config(Sensor, in5,    potRightClaw,   sensorPotentiometer)
#pragma config(Sensor, dgtl1,  encLDT,         sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encRDT,         sensorQuadEncoder)
#pragma config(Motor,  port2,           backLeft,      tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           leftClaw,      tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           leftDRFBY,     tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port5,           frontLeft,     tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           backRight,     tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           rightDRFBY,    tmotorVex393TurboSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port8,           rightClaw,     tmotorVex393TurboSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#pragma platform(VEX2)
#include "Vex_Competition_Includes.c"
#include "driving.c"
#include "auton.c"
//const int DIAMWHEELS = 4;
void pre_auton(){

}
task autonomous(){
	startTask(auton);
}
task usercontrol(){
	startTask(drive);
}

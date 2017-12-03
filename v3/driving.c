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

void sendByte(int byte) //Send 8 bits, most significant to least significant.
{
	for(int i = 128; i >= 1; i = i / 2)
	{
		SensorValue[data] = byte & i;
		SensorValue[clock] = 1;
		//This is where you may want to add a delay if it is being unreliable
		SensorValue[clock] = 0;
	}
}
void startTransmission() //Send Start Frame
{
	for(int i = 0; i < 4; i++)
	{
		sendByte(0);
	}
}

void endTransmission() //Send End Frame
{
	for(int i = 0; i < 4; i++)
	{
		sendByte(255);
	}
}
//Send a single LED frame, these get pushed down the strip as more and more are added
//Brightness: From 0 to 31, an LED-wide modifier to the brightness
//R,G,B: The RGB color value of the LED
void sendLEDFrame(int brightness, int r, int g, int b)
{
	sendByte(224 | brightness); //The brightness byte is 111xxxxx, there are only 5 bits that you can use
	sendByte(b);
	sendByte(g);
	sendByte(r);
}

//Sets the whole strip's color and brightness
//Length: How many LEDs are in the strip
//Brightness, R,G,B: Same as above
void setStripColor(int length, int brightness, int r, int g, int b) //Set the whole strip to a uniform color.
{
	startTransmission();
	for(int i = 0; i < length; i++)
	{
		sendLEDFrame(brightness, r, g, b);
	}
	endTransmission();
}
task fadeColors(){
	int r = 255;
	int g = 0;
	int b = 0;
	startTransmission();
	for(int i=0; i < 255; i++){
		sendLEDFrame(31, r, g, b);
		wait1Msec(4);
		g++;
	}
	endTransmission();
	startTransmission();
	for(int i=0; i < 255; i++){
		sendLEDFrame(31, r, g, b);
		wait1Msec(4);
		r--;
	}
	endTransmission();
	startTransmission();
	for(int i=0; i < 255; i++){
		sendLEDFrame(31, r, g, b);
		wait1Msec(4);
		b++;
	}
	endTransmission();
	startTransmission();
	for(int i=0; i < 255; i++){
		sendLEDFrame(31, r, g, b);
		wait1Msec(4);
		g--;
	}
	endTransmission();
	startTransmission();
	for(int i=0; i < 255; i++){
		sendLEDFrame(31, r, g, b);
		wait1Msec(4);
		r++;
	}
	endTransmission();
	startTransmission();
	for(int i=0; i < 255; i++){
		sendLEDFrame(31, r, g, b);
		wait1Msec(4);
		b--;
	}
	endTransmission();

}
task smoothWave(){
	int r = 255;
	int g = 0;
	int b = 0;
	startTransmission();
	for(g = 0; g<128; g++){
		sendLEDFrame(31,r,g,b);
		wait1Msec(4);
	}
	endTransmission();
	startTransmission();
	for(g = 128; g<255; g++){
		sendLEDFrame(31,r,g,b);
		wait1Msec(4);
	}
	endTransmission();
	startTransmission();
	for(r = 255; r>0; r--){
		sendLEDFrame(31,r,g,b);
		wait1Msec(4);
	}
	endTransmission();
	startTransmission();
	for(b = 0; b < 255; b++){
		g = 255 - b;
		sendLEDFrame(31,r,g,b);
		wait1Msec(4);
	}
	endTransmission();
	startTransmission();
	for(r = 0; r < 128; r++){
		sendLEDFrame(31,r,g,b);
		wait1Msec(4);
	}
	endTransmission();
	startTransmission();
	for(r = 128; r < 255; r++){
		b = 255-2*(r-128);
		sendLEDFrame(31,r,g,b);
		wait1Msec(4);
	}
	endTransmission();
}
task smoothWaveFullStrip(){
	int r = 255;
	int g = 0;
	int b = 0;
	startTransmission();
	for(g = 0; g<128; g++){
		setStripColor(120,31,r,g,b);
	}
	endTransmission();
	startTransmission();
	for(g = 128; g<255; g++){
		setStripColor(120,31,r,g,b);
	}
	endTransmission();
	startTransmission();
	for(r = 255; r>0; r--){
		setStripColor(120,31,r,g,b);
	}
	endTransmission();
	startTransmission();
	for(b = 0; b < 255; b++){
		g = 255 - b;
		setStripColor(120,31,r,g,b);
	}
	endTransmission();
	startTransmission();
	for(r = 0; r < 128; r++){
		setStripColor(120,31,r,g,b);
	}
	endTransmission();
	startTransmission();
	for(r = 128; r < 255; r++){
		b = 255-2*(r-128);
		setStripColor(120,31,r,g,b);
	}
	endTransmission();
}
int currentTowerAngle = 0;
int currentElbowAngle = 0;
task drive(){
	int c4 = 0;
	int c3 = 0;
	short r = 25, g = 0, b = 60;
	resetMotorEncoder(tower);
	resetMotorEncoder(elbow);
	while(true){
		currentTowerAngle = (392*SensorValue[towerEnc])/(5*360)+180;
		currentElbowAngle = (-627.2*SensorValue[elbowEnc])/(5*360) + currentTowerAngle;
		//set threshold to 20 and make sure it is zero under it
		const int THRESHOLD = 20;
		if(abs(vexRT[Ch4])>THRESHOLD)
			c4 = vexRT[Ch4];
		else
			c4 = 0;
		if(abs(vexRT[Ch3])>THRESHOLD)
			c3 = vexRT[Ch3];
		else
			c3 = 0;
		//
		motor[fldt] = motor[bldt] = c4+c3;
		motor[frdt] = motor[brdt] = -c4+c3;
		//
		if(vexRT[Btn5U])motor[mgml] = motor[mgmr] = 60;
		else if(vexRT[Btn5D])motor[mgml] = motor[mgmr] = -60;
		else motor[mgml] = motor[mgmr] = 0;
		//
		if(vexRT[Btn6U]==1){
			motor[claw]=127;
			}else if(vexRT[Btn6D]==1){
			motor[claw]=-127;
			}else{
			motor[claw]=0;
		}
		/*
		if(vexRT[Btn7L]==1){
			motor[tower]=100;
			motor[elbow]=100;
		}else if(vexRT[Btn7R]==1){
			motor[tower]=-100;
			motor[elbow]=-100;
		}else{
			motor[elbow]=(abs(vexRT[Ch1])>20?vexRT[Ch1]/3*2:0);
			motor[tower]=(abs(vexRT[Ch2])>20?vexRT[Ch2]/3*2:0);
		}
		*/
		if(vexRT[Btn7L]==1){
			moveMotorTarget(tower, 4, 50, true);
      		moveMotorTarget(elbow, 4, 50, true);
		}else if(vexRT[Btn7R]==1){
			moveMotorTarget(tower, -4, 50, true);
      		moveMotorTarget(elbow, -4, 50, true);
     	}else{
			moveMotorTarget(tower, vexRT[Ch1]/2, 75, true);
      		moveMotorTarget(elbow, vexRT[Ch2]/2, 75, true);
		}
		//sounds
		if(!bSoundActive){
			if(vexRT[Btn8R]==1){
				wait1Msec(100);
				playSoundFile("allstar.wav");
			}
			if(vexRT[Btn8U]==1){
				wait1Msec(100);
				playSoundFile("omae_wa_mou_shindeiru.wav");
			}
		}
		//
		if(vexRT[Btn7U]==1)startTask(fadeColors);
		if(vexRT[Btn7D]==1)startTask(smoothWave);
		if(vexRT[Btn8L]==1)startTask(smoothWaveFullStrip);
		if(vexRT[Btn8R]==1)g-=5;
		if(vexRT[Btn8U]==1)b+=5;
		if(vexRT[Btn8D]==1)b-=5;
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0,0,"Battery: ");
		displayLCDNumber(0,9, nImmediateBatteryLevel);
		displayLCDString(0,13, " mV");
		displayLCDString(1,0,"Backup: ");
		displayLCDNumber(1,9,BackupBatteryLevel);
		displayLCDString(1,13, " mV");
		wait1Msec(25);
	}
}

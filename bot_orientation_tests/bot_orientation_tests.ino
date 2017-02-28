//Copywrite 2017 LeRoy Miller.
//Based on time, and needs to be adjusted for different motors
//and different surface materials.

#include "BittyBot2.h"

int leftspeed = 75;
int rightspeed = 75;

int directionFlag = 1; //1 = Face UP, 2 = Face Right, 3 = Face Left, 4 = Face Down

int leftSensor = A0; 
int centerSensor = A1;
int rightSensor = A2;


BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right

void setup () {
	Serial.begin(9600);
	bot.begin();
  
	pinMode (leftSensor, INPUT);
  pinMode (centerSensor, INPUT);
  pinMode (rightSensor, INPUT);
  
	Serial.println("Hello!");
 
}

void loop() {

/*if (directionFlag > 4) {directionFlag = 1;}
findOrientation();
Serial.println("Main Loop");
directionFlag = directionFlag +1;
Serial.println(directionFlag);
delay(1000);
*/

findOrientation();
Serial.println("Main Loop");

}


void findOrientation() {

 bot.Speed(leftspeed, rightspeed);
 
 //Up
 if (directionFlag == 1) {
  if (digitalRead(leftSensor) == 1 && digitalRead(rightSensor) == 1 && digitalRead(centerSensor) == 0) {
 Serial.println("UP");
 bot.stop();
 Serial.println("DONE:");
 while(1) {} 
  }
  bot.rightTight(100);
 }

 //Right
 if (directionFlag == 2) {
  while(digitalRead(leftSensor) != 1 && digitalRead(rightSensor) != 0 && digitalRead(centerSensor) != 0) {
 Serial.println("Right");
 bot.rightTight(100);   
  }
  bot.update();
  bot.stop();
 }

 //Down
 if (directionFlag == 4) {
  while(digitalRead(leftSensor) != 0 && digitalRead(rightSensor) != 0 && digitalRead(centerSensor) != 0) {
 Serial.println("Down");
 bot.rightTight(100);   
  }
  bot.update();
  bot.stop();
 }

//Left
if (directionFlag == 3) {
  while(digitalRead(leftSensor) != 0 && digitalRead(rightSensor) != 1 && digitalRead(centerSensor) != 0) {
 Serial.println("Left");
 bot.rightTight(100);   
  }
  bot.update();
  bot.stop(); 
}

}



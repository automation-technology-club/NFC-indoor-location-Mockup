//Copywrite 2017 LeRoy Miller.
//Based on time, and needs to be adjusted for different motors
//and different surface materials.

#include "BittyBot2.h"

int leftspeed = 175;
int rightspeed = 175;

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

if (directionFlag > 4) {directionFlag = 1;}
findOrientation();
directionFlag ++;
delay(1000);

}

void turnleft() {
  //turn left about 90 degrees
  bot.Speed(leftspeed,rightspeed);
  bot.leftTight(360);
  while (bot.IsRunning()) {
    
    Serial.println(bot.IsRunning());
    bot.update();
      }
}

void findOrientation() {

 bot.Speed(leftspeed, rightspeed);
 
 //Up
 if (directionFlag == 1) {
  while(digitalRead(leftSensor) != 1 && digitalRead(rightSensor) != 1 && digitalRead(centerSensor) != 0) {
 bot.rightTight(100);   
  }
  bot.update();
  bot.stop();
 }

 //Right
 if (directionFlag == 2) {
  while(digitalRead(leftSensor) != 1 && digitalRead(rightSensor) != 0 && digitalRead(centerSensor) != 0) {
 bot.rightTight(100);   
  }
  bot.update();
  bot.stop();
 }

 //Down
 if (directionFlag == 4) {
  while(digitalRead(leftSensor) != 0 && digitalRead(rightSensor) != 0 && digitalRead(centerSensor) != 0) {
 bot.rightTight(100);   
  }
  bot.update();
  bot.stop();
 }

//Left
if (directionFlag == 3) {
  while(digitalRead(leftSensor) != 0 && digitalRead(rightSensor) != 1 && digitalRead(centerSensor) != 0) {
 bot.rightTight(100);   
  }
  bot.update();
  bot.stop(); 
}

}

void turnright() {
  //turn right about 90 degrees
  bot.Speed(leftspeed, rightspeed);
  bot.rightTight(360);
  while (bot.IsRunning()) {
    
    Serial.println(bot.IsRunning());
    bot.update();
      }
}


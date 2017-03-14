//Copywrite 2017 LeRoy Miller.
//Based on time, and needs to be adjusted for different motors
//and different surface materials.

#include "BittyBot2.h"

int leftspeed = 50;
int rightspeed = 50;
int turnDelay = 1500;

BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right

void setup () {
	Serial.begin(9600);
	bot.begin();
	
	Serial.println("Hello!");
}

void loop() {
  
	turnleft();
	Serial.println("Left!");

delay(1000);

Serial.println("Right!");
  turnright();

 Serial.println("End.");

 while(1) {}
}

void turnleft() {
  //turn left about 90 degrees
  bot.Speed(leftspeed,rightspeed);
  bot.leftTight(turnDelay); //360
  while (bot.IsRunning()) {
    
    Serial.println(bot.IsRunning());
    bot.update();
      }
}

void turnright() {
  //turn right about 90 degrees
  bot.Speed(leftspeed, rightspeed);
  bot.rightTight(turnDelay); //360
  while (bot.IsRunning()) {
    
    Serial.println(bot.IsRunning());
    bot.update();
      }
}


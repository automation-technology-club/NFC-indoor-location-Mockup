
#include <Arduino.h>
#include <Wire.h>
#include <HMC5883L_Simple.h>
#include "BittyBot2.h"

int leftspeed = 175;
int rightspeed = 175;
int targetHeading;
float startHeading;
float heading;

BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right
HMC5883L_Simple Compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bot.begin();
  Compass.SetDeclination(-7, 53, 'W');
  Compass.SetSamplingMode(COMPASS_SINGLE);
  Compass.SetScale(COMPASS_SCALE_130);
  Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
  delay(5000); //wait for robot to be placed on table
}

void loop() {
  bot.Speed(leftspeed,rightspeed);
  startHeading = Compass.GetHeadingDegrees();
  //right 90 degrees
  targetHeading = int(90 - startHeading);
  if (targetHeading < 0) { targetHeading +=360; }
Serial.println("Right Turn ");
Serial.print("Starting Heading: ");
Serial.println(startHeading);
Serial.print("Target Heading: ");
Serial.println(targetHeading);
   bot.rightTight(5000);
    while (bot.IsRunning()) {
      //heading = Compass.GetHeadingDegrees();
       //Serial.print("Current Heading: ");
  //Serial.println(int(heading));
 //if (int(heading) == targetHeading) {
  //  bot.stop();
  //  }
      bot.update();
    }

//while(1) {}
delay(8000);

/*startHeading = Compass.GetHeadingDegrees(); 
//left 90 degrees
targetHeading = int(360 - startHeading);
if (targetHeading < 0) { targetHeading +=360; }
Serial.println("Left Turn ");
Serial.print("Starting Heading: ");
Serial.println(startHeading);
Serial.print("Target Heading: ");
Serial.println(targetHeading);

while (int(heading) != targetHeading) {
bot.leftTight(25);
heading=Compass.GetHeadingDegrees();
Serial.print("Current Heading: ");
Serial.println(int(heading));
bot.update();
delay(100);
}
bot.stop();

/*
while (bot.IsRunning()) {
  heading = Compass.GetHeadingDegrees();
  if (int(heading) == targetHeading) {
    bot.stop();
    }
  bot.update();
}


  delay(8000);
*/  
}

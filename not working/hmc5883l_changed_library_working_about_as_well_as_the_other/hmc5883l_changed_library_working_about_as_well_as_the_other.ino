
#include <Arduino.h>
#include <Wire.h>
#include "I2Cdev.h"
#include "HMC5883L.h"
#include "BittyBot2.h"

int leftspeed = 175;
int rightspeed = 175;
int targetHeading;
float startHeading;
float heading;

BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right
HMC5883L Compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bot.begin();
  Compass.initialize();
  /*Compass.SetDeclination(-7, 53, 'W');
  Compass.SetSamplingMode(COMPASS_CONTINUOUS);
  Compass.SetScale(COMPASS_SCALE_190);
  Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
  */
  delay(5000); //wait for robot to be placed on table
}

void loop() {
    
  turn(90); //turn right
  bot.stop();
  delay(5000);
  turn(-90); //turn left back to start
  bot.stop();
  delay(1000);
turn(-90);
bot.stop();
delay(1000);
  while(1);
  
  
}

void turn(int angle) {
  int16_t mx, my, mz;
  Compass.getHeading(&mx, &my, &mz);
  //int originalAngle=Compass.GetHeadingDegrees();
  float originalAngle = atan2(my, mx);
  if (originalAngle<0) {originalAngle += 2*M_PI;} 
  originalAngle = originalAngle * 180/M_PI;
  //originalAngle = map(originalAngle, 0, 360, 246, 360);
  Serial.print("Str: ");
  Serial.println(originalAngle);
  int target=originalAngle+angle;
  //target= map(target, target, 360, 0, 360);
  //Serial.print("Trg: ");
  //Serial.println(target);
  //target=angle;
  uint8_t speed=80;
  target=target%360;
  //Serial.print("Upd Trg: ");
  //Serial.println(target);
  if(target<0){
    target+=360;
  }
  int direction=angle;
  while(1){
    //int currentAngle=Compass.GetHeadingDegrees();
    int16_t mx, my, mz;
  Compass.getHeading(&mx, &my, &mz);
  float currentAngle = atan2(my, mx);
  if (currentAngle<0) {currentAngle += 2*M_PI;} 
  currentAngle = currentAngle * 180/M_PI;
  //currentAngle = map(currentAngle, 0, 360, 246, 360);
    int diff=target-currentAngle;
    direction=180 - (diff+360)%360;
    
    if(direction>0){
      bot.Speed(speed,speed);//right
      bot.rightTight(50);
      Serial.print("Diff: ");
      Serial.println(diff);
      while (bot.IsRunning()) {
        bot.update();
      }
            
    }else{
      bot.Speed(speed,speed);//left
      bot.leftTight(50);
      Serial.print("Diff: ");
      Serial.println(diff);
      while (bot.IsRunning()) {
        bot.update();
      }
          }
    
    if(abs(diff)<60) {
      bot.stop();
      return;
    }
    //if (abs(diff)>100 && direction<0) {
     // bot.stop();
     // return;
    //}
  }
}


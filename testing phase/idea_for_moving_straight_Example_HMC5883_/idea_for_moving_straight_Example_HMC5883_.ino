/* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2014-06-22
Website: http://hobbylogs.me.pn/?p=17
Location: Pakistan
Ver: 0.1 beta --- Start
Ver: 0.2 beta --- Debug feature included
*/

#include <Wire.h>
#include "compass.h"
#include "BittyBot2.h"


BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right


void setup(){
  
  Serial.begin(9600);
  bot.begin();
  Serial.write(17);
  Wire.begin();
  //compass_x_offset = 122.17;
  //compass_y_offset = 230.08;
  //compass_z_offset = 389.85;
  compass_x_offset = 96.07;
  compass_y_offset = 483.79;
  compass_z_offset = 570.42;
  compass_x_gainError = 1.12;
  compass_y_gainError = 1.13;
  compass_z_gainError = 1.03;
  
  compass_init(2);
 // compass_debug = 1;
 // compass_offset_calibration(3);

Serial.write(12);
Serial.println("Ready...delay.");

delay(8000);

}


void loop() {
  /* There is still a issue * sometimes the robot turns right a little
   *  when it should turn left.
   *  
   *  A negitive angle/degree should turn the robot left
   *  A positive angle/degree should turn the robot right
   *  
   *  Right appears to be a lot more consistant than turning left.
   *  
   */
  
  //turn(180);
  straight(10000); 
  bot.stop();
  
  while(1);
}

void turn(int angle){
   compass_scalled_reading();
   compass_heading();
  Serial.write(12);
  Serial.print ("Heading= ");
  Serial.print (bearing);
  Serial.println(" Degree");
  
//start turning code
int originalAngle = bearing;
int target = originalAngle+angle;
uint8_t speed=100;
target=target%360;
if(target<0) {target+=360;}  

Serial.write(12);
Serial.print("target ");
Serial.print(target);

int direction=angle;
  while(1){
    compass_scalled_reading();
    compass_heading();
    int currentAngle=bearing;
    int diff=target-currentAngle;
    direction=180 - (diff+360)%360;

    Serial.write(12);
    Serial.print("Current: ");
    Serial.print(currentAngle);
    
    if(direction>0){
     bot.Speed(speed,speed);//right
     bot.rightTight(50);
      Serial.write(12);
      Serial.print("Right");
      while (bot.IsRunning()) {
        bot.update();
      }
            
    }else{
     bot.Speed(speed,speed);//left
     bot.leftTight(50);
      Serial.write(12);
      Serial.print("Left");
      while (bot.IsRunning()) {
        bot.update();
      }
          }
    
    if(abs(diff)<9 ) {
      bot.stop();
      Serial.write(12);
      Serial.println("DONE!");
      return;
    }
    delay(66);
  }  
}

void straight(int interval){
   compass_scalled_reading();
   compass_heading();
  Serial.write(12);
  Serial.print ("Heading= ");
  Serial.print (bearing);
  Serial.println(" Degree");
  
//start turning code
int originalAngle = bearing;
int target = originalAngle;
uint8_t speed=175;
target=target%360;
if(target<0) {target+=360;}  

Serial.write(12);
Serial.print("target ");
Serial.print(target);
unsigned long currentMillis = millis();
int previousMillis = currentMillis;
int direction=target;
  while(currentMillis - previousMillis <= interval) {
    compass_scalled_reading();
    compass_heading();
    int currentAngle=bearing;
    int diff=target-currentAngle;
    direction=180 - (diff+360)%360;

    Serial.write(12);
    Serial.print("Current: ");
    Serial.print(currentAngle);
    
    if(direction>0){
     bot.Speed(speed,speed);//right
     bot.right(50);
      Serial.write(12);
      Serial.print("Right");
      while (bot.IsRunning()) {
        bot.update();
      }
            
    }else{
     bot.Speed(speed,speed);//left
     bot.left(50);
      Serial.write(12);
      Serial.print("Left");
      while (bot.IsRunning()) {
        bot.update();
      }
          }
    currentMillis = millis();
    previousMillis = currentMillis;
   // if(abs(diff)<9 ) {
    //  bot.stop();
    //  Serial.write(12);
    //  Serial.println("DONE!");
    //  return;
    //}
    delay(66);
  }  
  bot.stop();
}










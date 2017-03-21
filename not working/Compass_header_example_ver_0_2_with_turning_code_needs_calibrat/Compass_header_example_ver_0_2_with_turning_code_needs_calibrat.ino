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
int leftspeed = 175;
int rightspeed = 175;
int targetHeading;
float startHeading;
float heading;

BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right

#define Task_t 10          // Task Time in milli seconds

int dt=0;
unsigned long t;
// Main code -----------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  bot.begin();
  Serial.write(17);
  // Serial.print("Setting up I2C ........\n");
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
  compass_debug = 1;
  compass_offset_calibration(3);

Serial.write(12);
Serial.println("Ready...delay.");

delay(8000);

}

// Main loop 
// Main loop -----------------------------------------------------------------

void loop() {
  turn(90); 
  bot.stop();
  delay(5000);
  turn(-90);
  bot.stop();
  delay(1000);
  turn(90);
  bot.stop();
  delay(1000);
  turn(-180);
  bot.stop();
  while(1);
}




void turn(int angle){
  
  t = millis();
  float load;
   compass_scalled_reading();
  //Serial.print("x = ");
  //Serial.println(compass_x_scalled);
  //Serial.print("y = ");
  //Serial.println(compass_y_scalled);
  //Serial.print("z = ");
  //Serial.println(compass_z_scalled);
   compass_heading();
  Serial.write(12);
  Serial.print ("Heading= ");
  Serial.print (bearing);
  Serial.println(" Degree");
  
  dt = millis()-t;
  load = (float)dt/(Task_t/100);
  //Serial.print ("Load on processor = ");
  //Serial.print(load);
  //Serial.println("%");

//start turning code
int originalAngle = bearing;
int target = originalAngle+angle;
uint8_t speed=80;
target=target%360;
if(target<0) {target+=360;}  

int direction=angle;
  while(1){
    compass_scalled_reading();
  //Serial.print("x = ");
  //Serial.println(compass_x_scalled);
  //Serial.print("y = ");
  //Serial.println(compass_y_scalled);
  //Serial.print("z = ");
  //Serial.println(compass_z_scalled);
   compass_heading();
  Serial.write(12);
  Serial.print ("Heading= ");
  Serial.print (bearing);
  Serial.println(" Degree");
  int currentAngle=bearing;
    int diff=target-currentAngle;
    direction=180 - (diff+360)%360;
    
    if(direction>0){
      bot.Speed(speed,speed);//right
      bot.rightTight(50);
      //Serial.print("Diff: ");
      //Serial.println(diff);
      while (bot.IsRunning()) {
        bot.update();
      }
            
    }else{
      bot.Speed(speed,speed);//left
      bot.leftTight(50);
      //Serial.print("Diff: ");
      //Serial.println(diff);
      while (bot.IsRunning()) {
        bot.update();
      }
          }
    
    if(abs(diff)<9 ) {
      bot.stop();
      return;
    }
    /*if (abs(diff)>114) {
      bot.stop();
      return;
    }*/
  }  
}












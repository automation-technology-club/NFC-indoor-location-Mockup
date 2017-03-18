//This is a simple working-example to quick measuring:
//1. the x, y and z-values read from a GY-61-acceleration-module
//2. an angle in eg. the x-direction

/* You can put the module in 4 directios to determine the min-max-values:
 *  _> 0deg x = 349 y = 341 z = 425
 *  ^ 90 deg x= 281 y = 345 z = 357
 *  <_ 180 deg x = 350 y = 345 z = 288
 *  V 270 deg x = 419 y = 341 z = 355
 *  This can be used to measure degrees
 */

 //you can use all the analog inputs to control the GY-61
 //picture: https://www.fabtolab.com/ADXL335-GY61?search=gy-61

#include <BittyBot2.h>

int leftspeed = 75;
int rightspeed = 75;

BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right


 const int VCCPin = A0;
 const int xPin = A1;
 const int yPin = A2;
 const int zPin = A3;
 const int GNDPin = A4;

 //variables
 int x=0;
 int y=0;
 int z=0;
 int angle = 0;
 int currentHeading = 0;
 int targetHeading = 0;
 
void setup() {
  // pin A0 (pin 14) is VCC and pin A4 (pin18) is GND to activate the GY-61 module
  pinMode(A0, OUTPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(54, HIGH);
  digitalWrite(58, LOW);

//activating debugging for arduino UNO
Serial.begin(9600);
bot.begin();
}


void loop() {
  updateXYZ();
  currentHeading = angle;
  targetHeading = (currentHeading += 90);
   if (targetHeading > 360) {targetHeading -=360;}
  turnleft90();
  while (1);
}

void turnleft90() {
  while (currentHeading <= targetHeading) {
  bot.Speed(leftspeed,rightspeed);
  bot.leftTight(1000);
  while(bot.IsRunning()) {
    bot.update();
    updateXYZ();
  }
  }
  bot.stop();
}

void updateXYZ() {

x = analogRead(xPin);
y = analogRead(yPin);
z = analogRead(zPin);

//show x, y and z-values
Serial.print("X = ");
Serial.print(x);
Serial.print(" y = ");
Serial.print(y);
Serial.print(" z = ");
Serial.print(z);

//show angle
Serial.print(" Angle = ");
//Serial.println(constrain(map(x,349,281,0,90),0,90));
//angle = constrain(map(x,342,328,413,90),0,90);
angle = constrain(map(y,z,x,0,360),0,360);
Serial.println(angle);
//delay(250);


}



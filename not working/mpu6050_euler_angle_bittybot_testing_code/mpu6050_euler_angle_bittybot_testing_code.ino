#include <BittyBot2.h>

int leftspeed = 50;
int rightspeed = 50;

BittyBot bot(44,46,36,38,40,42); //Left Enable, Right Enable, Pin1 for Left, Pin2 for Left, Pin 1 for Right, Pin 2 for Right

int currentHeading;
int targetHeading;
int error = 999;
int count = 0;

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
MPU6050 mpu;
#define OUTPUT_READABLE_EULER
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  bot.begin();
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(9600);
    Serial.write(17);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

   mpu.initialize();

    
   devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
  /*  mpu.setXGyroOffset(38);
    mpu.setYGyroOffset(-91);
    mpu.setZGyroOffset(46);
    mpu.setZAccelOffset(1682); // 1688 factory default for my test chip
*/

 // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(300); //220
    mpu.setYGyroOffset(1); //76
    mpu.setZGyroOffset(24);
    mpu.setZAccelOffset(2567);
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {

        mpu.setDMPEnabled(true);

        
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================


void loop() {
  targetHeading = 00;
    readMPU();
   targetHeading = (currentHeading += 90);
   if (targetHeading > 360) {targetHeading -=360;}
   
  // Serial.print("Target Heading: ");
   //Serial.println(targetHeading);
   //Serial.print("Error: ");
  // error = currentHeading - targetHeading;
   //if (error<180) {error +=360;}
   //if (error>180) {error -=360;}
   //Serial.println(error);

//int startHeading = currentHeading;
//Serial.print("Start Heading: ");
//Serial.println(startHeading);
readMPU();

//while (currentHeading - targetHeading != targetHeading % 5) {
while (currentHeading != targetHeading ) {
//while((100*(targetHeading-currentHeading)/currentHeading)+100 != 5) {
  readMPU();
    //Serial.print("Target Heading: ");
   //Serial.println(targetHeading);
   //Serial.print("Error: ");
   /*error += currentHeading - targetHeading;
   if (error<180) {error +=360;}
   if (error>180) {error -=360;}
   Serial.println(error);
   */
   //Serial.println(currentHeading - targetHeading);
   bot.Speed(leftspeed,rightspeed);
   bot.leftTight(10);
   while(bot.IsRunning()) {
    bot.update();
    readMPU();
   }
   //delay(250);
     }
     
     bot.stop();
  readMPU();
  //Serial.print("Current Heading: ");
  //Serial.println(currentHeading);
  //Serial.print("Target Heading: ");
  //Serial.println(targetHeading);
  //Serial.print("Start Heading: ");
  //Serial.println(startHeading);
  //Serial.print("Error: ");
  //Serial.println(error);
  //Serial.print("Error / Count: ");
  //Serial.println(error/count);
  Serial.println("DONE!");
  while(1);
   
}

void readMPU() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

// display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetEuler(euler, &q);
           // Serial.print("euler\t");
           // Serial.println(euler[0] * 180/M_PI);
//            Serial.print("\t");
//            Serial.print(euler[1] * 180/M_PI);
//            Serial.print("\t");
//            Serial.println(euler[2] * 180/M_PI);
      //Serial.print("Heading: ");
      //Serial.println((euler[0]* 180/M_PI)+180);
  currentHeading = ((euler[0]*180/M_PI)+180);

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
    //delay(200);
}

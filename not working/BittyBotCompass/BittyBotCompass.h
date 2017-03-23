/* BittyBot Motor Library version 2
created by LeRoy Miller, Oct 3, 2015
*/

#ifndef BittyBot2_h
#define BittyBot2_h

#include "Arduino.h"

class BittyBot {
private:
	int _enableL;
	int _enableR;
	int _Left1; //L1 
	int _Left2; //L2
	int _Right1; //L3
	int _Right2; //L4
	unsigned long _previousMillis;
	long _OnTime;
	int _speedL;
	int _speedR;
  int _isrunning;
public: 
BittyBot(int enableL, int enableR, int Left1, int Left2, int Right1, int Right2); 
void begin();
void Speed(int speedL, int speedR);
void stop();
void forward(int OnTime);
void back(int OnTime);
void rightTight(int OnTime);
void leftTight(int OnTime);
void right(int OnTime);
void left(int OnTime);
void update();
void calibrate();
int IsRunning();

//added from compass.h
/* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2014-06-22
Website: http://hobbylogs.me.pn/?p=17
Location: Pakistan
Ver: 0.1 beta --- Start
Ver: 0.2 beta --- Debug feature included
*/
extern float bearing;
  extern float compass_x_scalled;
  extern float compass_y_scalled;
  extern float compass_z_scalled;
  
  extern float compass_x_offset, compass_y_offset, compass_z_offset;
  extern float compass_x_gainError,compass_y_gainError,compass_z_gainError;
  
  extern int compass_debug;
  
  void compass_read_XYZdata();
  void compass_offset_calibration(int select);
  void compass_init(int gain);
  void compass_scalled_reading();
  void compass_heading();
  
};

#endif

/*Mockup for mapping system using NFC tags for indoor robot 
 * location system.
 * 
 * Copyright(c) 2017, LeRoy Miller
 * 
 * Currently working on a UNO, but will probably need a MEGA
 * after NFC reader is added, and Bittybot library is added.
 * 
 * A compass maybe used for turning the robot left and right.
 * 
 */


int start = 20; //mockup starting location, this will be read by the NFC reader
int target = 1; //Target location to move the robot too
int targetrow;
int targetcol;
int row;
int col;
int codes[5][4] = {
  {1,2,3,4},
  {5,6,7,8},
  {9,10,11,12},
  {13,14,15,16},
  {17,18,19,20}
};  //Map of NFC codes (currently just numbers) will be codes read

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Current Map:");
int a, b;
  for (a = 0; a < 5; a++) {
    for (b = 0; b < 4; b++) {
      Serial.print(codes[a][b]);
      Serial.print(' ');
    }
    Serial.println();
      }
      Serial.println();
  Serial.print("Target: ");
  Serial.println(target);
  Serial.print("Target location: ");
  findnumbers(target);
  targetrow = row;
  targetcol = col;
  Serial.print("Robot Start: ");
  Serial.println(start);
  Serial.print("Start Location: ");
  findnumbers(start);
  calculatemove();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void findnumbers(int findnumber) {
int a, b;
  for (a = 0; a < 5; a++) {
    for (b = 0; b < 4; b++) {
      if (findnumber == codes[a][b]) {
        row = a;
        col = b;}
      }
  }
  Serial.print(row);
  Serial.print(",");
  Serial.println(col);
}

void calculatemove() {

/*This is the logic for the move, but currently only tells
 * a direction and how far the robot should move, it will should
 * recalculate each time it reads a new NFC tag, until target is
 * reached.
 */

  if (targetrow > row) {
    Serial.print("Move down ");
    Serial.print(targetrow - row);
    Serial.println(" rows.");
      }
  if (targetrow < row) {
    Serial.print("Move up ");
    Serial.print (row - targetrow);
    Serial.println(" rows.");
  }
  if (targetrow == row) {
    Serial.println("We are on the correct row.");   
  }
  if (targetcol > col) {
    Serial.print("Move ");
    Serial.print(targetcol - col);
    Serial.println(" columns to the right");
  }
  if (targetcol < col) {
    Serial.print("Move ");
    Serial.print(col - targetcol);
    Serial.println(" columns to the left.");
  }
  if (targetcol == col) {
    Serial.println("At the target column");
  }
  if (targetcol == col && targetrow == row) {
    Serial.println("We are at target.");
  }
}


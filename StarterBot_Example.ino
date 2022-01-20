//Include required libraries
#include <PPMReader.h>
#include <Servo.h>
#include <EEPROM.h>// EEPROM pre-installed library

//Instantiate servo motor objects, names can be changed
//Servo servo_Name;
Servo LARM;
Servo RARM;
Servo GRIPPER; // Originally LARM

//Global Pins Assignment for motor pins, and motor enable pins
//IN1-IN4 pins can be connected to both digital and analog pins
//EN1-EN2 pins to be connected to D3, D5, D6, D9, D10, or D11
//const int pin_Name = pin_Number;
const int FL_FwdPin = 8; //D0
const int FL_BwdPin = 9; //D1
const int BL_FwdPin = 10; //D2
const int BL_BwdPin = 11; //D3
const int L_EN = 5;
const int FR_FwdPin = A0; //A0
const int FR_BwdPin = A1; //A1
const int BR_FwdPin = A2; //A2
const int BR_BwdPin = A3; //A3
const int R_EN = 6;

//Controller settings, do not change
byte interruptPin = 3;
byte channelAmount = 8;
PPMReader ppm(interruptPin, channelAmount);

//Initialize global variables
//These are used in the calculation for the robot's wheel speed
//when it is turning left/right
int turn_Speed = 0;
int L_Speed = 1;
int R_Speed = 1;
bool Dir = true; //Forward = true, Backward = false

void setup() {
  //Setting the L298N pins as output pins
  //pinMode(pin_Name, OUTPUT);
  pinMode(FL_FwdPin, OUTPUT);
  pinMode(FL_BwdPin, OUTPUT);
  pinMode(BL_FwdPin, OUTPUT);
  pinMode(BL_BwdPin, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(FR_FwdPin, OUTPUT);
  pinMode(FR_BwdPin, OUTPUT);
  pinMode(BR_FwdPin, OUTPUT);
  pinMode(BR_BwdPin, OUTPUT);
  pinMode(R_EN, OUTPUT);

//  pinMode(SERVO_ARMS_PIN, OUTPUT);
//  pinMode(GRIPPER_PIN, OUTPUT);
//  pinMode(MANUAL_CONTROL_PIN, OUTPUT);
  LARM.attach(A4);
  RARM.attach(A5);
  GRIPPER.attach(A6);
  RARM.write(90); // Right arm is the right one // We will be using 90-180, 90 is upright 180 is front facing downwards
  LARM.write(90);
  GRIPPER.write(30);
//  Serial.println(GRIPPER_SERVO.read());

  //Start serial comm for troubleshooting through serial monitor
  //Serial.begin(baud rate);
  Serial.begin(115200);
}



void loop() {
    int c1 = readChannel(1);
    int c2 = readChannel(2);
    int c3 = readChannel(3);
    int c4 = readChannel(4);
    int c5 = readChannel(5);
  
    //If the left stick is pushed down, wheels on both sides will
    //rotate forward. Speed of both sides will be calculated
    //with the "speed_Check" function.
    if (c2 >= 1000 and c2 < 1450) {
      movBackward(c1, c2);
    }
    //If the left stick is pushed up, wheels on both sides
    //will rotate backwards.
    else if (c2 <= 2000 and c2 > 1550) {
      movForward(c1, c2);
    }
    //If the left stick is stationary (in the middle)
    else {
      //If the right stick is pushed left, left wheel will rotate
      //backwards, while the right wheel will rotate forward.
      //Rotation speed will be calculated using "rotate" function.
      if (c1 >= 1000 and c1 < 1450) {
        rotateLeft(c1, c2);
      }
      //If the right stick is pushed right,left wheel will rotate
      //forward, while the right wheel will rotate backwards.
      else if (c1 <= 2000 and c1 > 1550) {
        rotateRight(c1, c2);
      }
      //If the right stick is stationary (in the middle),
      //stop the robot from moving
      else {
        stopMovement();
      }
    }
  
    //INSERT GRIPPER CODE HERE
    if (c3 >= 1000 and c3 < 1450) {
      int armAngle = map(c3, 1000, 1450, 45, 135);
//      Serial.println(armAngle);
      RARM.write(armAngle);
      LARM.write(180 - armAngle);
    } else if (c3 > 1550 and c3 <= 2000) {
      int armAngle = map(c3, 1550, 2000, 135, 180);
//      Serial.println(armAngle);
      RARM.write(armAngle);
      LARM.write(180 - armAngle);
    }
//    if (c4 >= 1000 and c4 <= 2000) {
//      int gripperAngle = map(c4, 1000, 2000, 90, 0);
//      GRIPPER.write(gripperAngle);
//      GRIPPER.read();
//      Serial.println(gripperAngle);
//    }
  
  delay(10);
}

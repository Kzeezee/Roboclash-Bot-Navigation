// Navigation modes
void movBackward(int c1, int c2) { // navMode 0
  leftBwd();
  rightBwd();
  Dir = false;
  speed_Check(Dir, c2, c1, 1450, 1000);
}

void movForward(int c1, int c2) { // navMode 1
  leftFwd();
  rightFwd();
  Dir = true;
  speed_Check(Dir, c2, c1, 1550, 2000);
}

void rotateLeft(int c1, int c2) { // navMode 2
  leftBwd();
  rightFwd();
  rotate(c1, 1450, 1000);
}

void rotateRight(int c1, int c2) { // navMode 3
  leftFwd();
  rightBwd();
  rotate(c1, 1550, 2000);
}

void stopMovement() { // navMode 4
  leftStop();
  rightStop();
}

// Tuning for navigation
void speed_Check(bool dir, int throttle_Val,int steering_Val, int l_Limit, int r_Limit) {
  //Set minimum value for the motors to be 127
  //Map the input values from the controller to the
  //motors' speed value
  L_Speed = map(throttle_Val, l_Limit, r_Limit, 127, 255);
  R_Speed = map(throttle_Val, l_Limit, r_Limit, 127, 255);

  //If the right stick is pushed left,
  //1. robot will steer left if moving forward
  //2. robot will steer right if moving backwards
  if (steering_Val >= 1000 and steering_Val < 1400){
    turn_Speed = map(steering_Val, 1400, 1000, 0, 127);
    L_Speed = abs(L_Speed + (-2 * dir + 1)*turn_Speed);
    R_Speed = abs(R_Speed + (2 * dir - 1)*turn_Speed);
  }
  //If the right stick is pushed right,
  //1. robot will steer right if moving forward
  //2. robot will steer left if moving backwards
  else if (steering_Val <= 2000 and steering_Val > 1600){
    turn_Speed = map(steering_Val, 1600, 2000, 0, 127);
    L_Speed = abs(L_Speed + (2 * dir - 1)*turn_Speed);
    R_Speed = abs(R_Speed + (-2 * dir + 1)*turn_Speed);
  }
  //if the right stick is stationary, continue as per normal
  else{
    L_Speed = map(throttle_Val, l_Limit, r_Limit, 127, 255);
    R_Speed = map(throttle_Val, l_Limit, r_Limit, 127, 255);
  }

  //Limit the wheel's speed value to 255
  if(L_Speed > 255){L_Speed = 255;}
  if(R_Speed > 255){R_Speed = 255;}
  //Control the wheel's speed via PWM
  analogWrite(L_EN, L_Speed);
  analogWrite(R_EN, R_Speed);
}

void rotate(int rotate_Val, int l_Limit, int r_Limit){
    L_Speed = map(rotate_Val, l_Limit, r_Limit, 127, 255);
    R_Speed = map(rotate_Val, l_Limit, r_Limit, 127, 255);
    analogWrite(L_EN, L_Speed);
    analogWrite(R_EN, R_Speed);
}

void leftFwd() {
  digitalWrite(FL_FwdPin, HIGH);
  digitalWrite(FL_BwdPin, LOW);
  digitalWrite(BL_FwdPin, HIGH);
  digitalWrite(BL_BwdPin, LOW);
}

void leftBwd() {
  digitalWrite(FL_FwdPin, LOW);
  digitalWrite(FL_BwdPin, HIGH);
  digitalWrite(BL_FwdPin, LOW);
  digitalWrite(BL_BwdPin, HIGH);
}

void leftStop() {
  digitalWrite(FL_FwdPin, LOW);
  digitalWrite(FL_BwdPin, LOW);
  digitalWrite(BL_FwdPin, LOW);
  digitalWrite(BL_BwdPin, LOW);
}

void rightFwd() {
  digitalWrite(FR_FwdPin, HIGH);
  digitalWrite(FR_BwdPin, LOW);
  digitalWrite(BR_FwdPin, HIGH);
  digitalWrite(BR_BwdPin, LOW);
}

void rightBwd() {
  digitalWrite(FR_FwdPin, LOW);
  digitalWrite(FR_BwdPin, HIGH);
  digitalWrite(BR_FwdPin, LOW);
  digitalWrite(BR_BwdPin, HIGH);
}

void rightStop() {
  digitalWrite(FR_FwdPin, LOW);
  digitalWrite(FR_BwdPin, LOW);
  digitalWrite(BR_FwdPin, LOW);
  digitalWrite(BR_BwdPin, LOW);
}

// Gripper Controls
//void manualControl(int armsValue, int gripperValue) {
//  digitalWrite(MANUAL_CONTROL_PIN, HIGH);
//  armsValue = map(armsValue, 1000, 2000, 0, 180);
//  gripperValue = map(gripperValue, 1000, 2000, 0, 180);
//  Serial.print(armsValue);
//  Serial.print(" , ");
//  Serial.print(gripperValue);
//  Serial.println();
//  analogWrite(SERVO_ARMS_PIN, armsValue);
//  analogWrite(GRIPPER_PIN, gripperValue);
//}
//
//void transferControl() {
//  digitalWrite(MANUAL_CONTROL_PIN, LOW);
//}

// Auto modes
//void startAutoMode() {
//  
//}
//
//void stopAutoMode() {
//  
//}

// Recording modes
//void recordSeq(byte navMode) {
//  if (navMode == currentNavMode) {
//    sameRecStep = true;
//  } else {
//    sameRecStep = false;
//    sameRecTime = millis();
//  }
//  if (!sameRecStep) {
//    currentNavMode = navMode;
//    navMode[seq] = navMode;
//  } else {
//    navModeTime[seq] = millis() - sameRecTime;
//    seq++;
//  }
//}

// Utility
int readChannel(int channelNumber) {
  unsigned value = ppm.latestValidChannelValue(channelNumber, 0);
//  Serial.print(value);
//  Serial.print(", ");
  return value;
}

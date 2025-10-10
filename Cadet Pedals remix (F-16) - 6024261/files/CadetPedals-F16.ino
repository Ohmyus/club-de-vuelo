#include <Joystick.h>

//Joystick Setup
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  0, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X, Y, & Z Axis
  true, true, true,     // Rx, Ry, or No Rz
  false, false,          // Rudder but no throttle
  false, false, false);  // No accelerator, brake, or steering;
int leftPedal = 0;
int rightPedal = 0;
int rudderAxis_ = 0;                 

void setup(){
  Serial.begin(9600); //Start serial monitoring
  Joystick.begin(); //Starts joystick
}
  
void loop(){
  
  leftPedal = analogRead(A3);
  leftPedal = map(leftPedal,0,1023,255,0);
  Joystick.setRxAxis(leftPedal);
  
  rightPedal = analogRead(A2);
  rightPedal = map(rightPedal,0,1023,0,255);
  Joystick.setRyAxis(rightPedal);

  rudderAxis_ = analogRead(A1);
  rudderAxis_ = map(rudderAxis_,0,1023,0,255);
  Joystick.setRzAxis(rudderAxis_);

  delay(5);
}
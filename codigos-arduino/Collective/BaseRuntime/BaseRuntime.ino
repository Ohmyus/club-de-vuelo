// code for the collective base

#include <Wire.h> 
#include <Joystick.h>

#define register_1 0x03
#define register_2 0X04

unsigned long a, b, c, d;
unsigned long headState;
int encoderAddress = 0x06; //Defautl address of the MT6701 magnetic encoder, don't know yet how to change it
unsigned int lowbyte, highbyte, rawAngle;

Joystick_ Joystick(0x14, JOYSTICK_TYPE_JOYSTICK, 15, 0, false, false, false, false, false, true, false, true, false, false, false);

const bool initAutoSendState = true;

int rzAxis_ = 0;
int throttle_ = 0;

//Declaring Buttons
int lastButtonState[15];
int currentButtonState[15];


void setup() 
{ 
  Wire.begin();
  Joystick.begin();
  Joystick.setRzAxisRange(0,2500);
} 
 
void loop() 
{ 
  Wire.requestFrom(2, 4);    // request 4 bytes from the head arduino 
  while(Wire.available())
  { 
    a = Wire.read(); // receive a byte as character
    b = Wire.read();
    c = Wire.read();
    d = Wire.read();
  } 
  headState = a | b << 8 | c << 16 | d << 24;

  //buttons runtime:
  for (int buttonID = 0; buttonID < 15; buttonID++) {
    currentButtonState[buttonID] = bitRead(headState, buttonID);
    if (currentButtonState[buttonID] != lastButtonState[buttonID]) {
      Joystick.setButton(buttonID, currentButtonState[buttonID]);
      lastButtonState[buttonID] = currentButtonState[buttonID];
    }
  }

  //Throttle runtime:
  throttle_ = headState >> 22;
  Joystick.setThrottle(throttle_);

  //Collective rotation runtime:
  Wire.beginTransmission(encoderAddress);
  Wire.write(register_1);
  Wire.write(register_2);

  Wire.endTransmission();

  Wire.requestFrom(encoderAddress, 2);
  if(Wire.available() <= 2) {
    highbyte = Wire.read();
    lowbyte = Wire.read();
  }
  highbyte = highbyte << 6;
  lowbyte = lowbyte >> 2;

  rzAxis_ = highbyte | lowbyte;
  Joystick.setRzAxis(rzAxis_);

  delay(20);
}
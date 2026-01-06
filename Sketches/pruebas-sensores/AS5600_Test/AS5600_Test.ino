#include <Wire.h>
#include <Joystick.h>

int encoderAddress = 0x36; //Defautl address of the AS5600 magnetic encoder, don't know yet how to change it
unsigned int lowbyte0, highbyte0, rawAngle0;
unsigned int lowbyte1, highbyte1, rawAngle1;
float auxiliary0, degAngle0;
float auxiliary1, degAngle1;

#define register_1 0x0D
#define register_2 0X0C

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK , 0, 0,
  false, false, true, false, false, false,
  false, false, false, false, false);

const bool initAutoSendMode = true;



void setup () {
  Joystick.begin();
  Joystick.setZAxisRange(0,6000);
  Wire.begin();
  Wire.setClock(100000);
  Serial.begin(115200);

}
void getAngle0() {
  Wire.beginTransmission(encoderAddress);
  Wire.write(register_2);
  Wire.endTransmission();
  Wire.requestFrom(encoderAddress, 1);

  while (Wire.available()== 0);
  lowbyte0 = Wire.read();

  Wire.beginTransmission(encoderAddress);
  Wire.write(register_1);
  Wire.endTransmission();
  Wire.requestFrom(encoderAddress, 1);

  while (Wire.available()== 0);
  highbyte0 = Wire.read();


  highbyte0 = highbyte0 << 8;

  rawAngle0 = highbyte0 | lowbyte0;
  auxiliary0 = rawAngle0;
  degAngle0 = 360*auxiliary0/16384;
  delay(5);
}

void loop () {
  getAngle0();
  Serial.println(rawAngle0);
  Joystick.setZAxis(rawAngle0);
  delay(10);
}
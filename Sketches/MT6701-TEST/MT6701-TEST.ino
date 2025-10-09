#include <Wire.h>

int encoderAddress = 0x06; //Defautl address of the MT6701 magnetic encoder, don't know yet how to change it
unsigned int lowbyte0, highbyte0, rawAngle0;
unsigned int lowbyte1, highbyte1, rawAngle1;
float auxiliary0, degAngle0;
float auxiliary1, degAngle1;

#define register_1 0x03
#define register_2 0X04

void setup () {
  Wire.begin();
  Serial.begin(115200);

}
void loop () {
  getAngle0();
  Serial.println(rawAngle0);
  delay(10);
}

void getAngle0() {
  Wire.beginTransmission(encoderAddress);
  Wire.write(register_1);
  Wire.write(register_2);

  Wire.endTransmission();

  Wire.requestFrom(encoderAddress, 2);
  if(Wire.available() <= 2) {
    highbyte0 = Wire.read();
    lowbyte0 = Wire.read();
  }
  highbyte0 = highbyte0 << 6;
  lowbyte0 = lowbyte0 >> 2;

  rawAngle0 = highbyte0 | lowbyte0;
  auxiliary0 = rawAngle0;
  degAngle0 = 360*auxiliary0/16384;
  delay(5);
}

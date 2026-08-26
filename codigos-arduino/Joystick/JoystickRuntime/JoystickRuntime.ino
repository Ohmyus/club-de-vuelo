#include <PicoGamepad.h>
#include <Wire.h>

//Defining the button matrix pins
byte outputPins[5] = {0,1,2,3,4};
byte inputPins[5] = {14,15,26,27,28};

//Defining the axis variables
int encoderAddress = 0x06; //Default address of the MT6701 magnetic encoder, don't know yet how to change it
unsigned int lowbyte0, highbyte0, rawAngle0;
unsigned int lowbyte1, highbyte1, rawAngle1;
float degAngle0;
float degAngle1;
double auxiliary0, auxiliary1;

#define register_1 0x03 //first angle information register
#define register_2 0X04 //second angle information register

//Creating a PicoGamepad object
PicoGamepad gamepad;

//Declaring Buttons
  int buttonID = 0;
  int lastButtonState[25];
  int currentButtonState[25];
  

void setup() {
  //setting up I2C communication
  Wire.begin();
  Wire1.begin();
  //setting up the inputs
  for (int i = 0; i < 5; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  //setting up the outputs
  for (int i = 0; i < 5; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
}

void loop () {
  getAngle0();
  Serial.print(" ");
  getAngle1();
  matrixRuntime();
  gamepad.send_update();
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
  gamepad.SetX(auxiliary0);
  delay(5);
}
void getAngle1() {
  Wire1.beginTransmission(encoderAddress);
  Wire1.write(register_1);
  Wire1.write(register_2);

  Wire1.endTransmission();

  Wire1.requestFrom(encoderAddress, 2);
  if(Wire1.available() <= 2) {
    highbyte1 = Wire1.read();
    lowbyte1 = Wire1.read();
  }
  highbyte1 = highbyte1 << 6;
  lowbyte1 = lowbyte1 >> 2;


  rawAngle1 = highbyte1 | lowbyte1;
  auxiliary1 = rawAngle1;
  degAngle1 = 360*auxiliary1/16384;
  gamepad.SetY(auxiliary1);
  delay(5);
}
void matrixRuntime() {
  //ButtonMatrixRuntime
  for (int i = 0; i <5; i++) {
    digitalWrite(outputPins[i], LOW);
    //Serial.print("Pongo en LOW la columna");
    //Serial.println(i);
    //delay(500);
    for (int j = 0; j < 5; j++) {
      //delay(1000);
      buttonID = i + 5*j;
      currentButtonState[buttonID] = !digitalRead(inputPins[j]);
      if (currentButtonState[buttonID] != lastButtonState[buttonID]) {
        Joystick.setButton(buttonID, currentButtonState[buttonID]);
        lastButtonState[buttonID] = currentButtonState[buttonID];
      }
    }
    digitalWrite(outputPins[i], HIGH);
    delayMicroseconds(5);
  }
}



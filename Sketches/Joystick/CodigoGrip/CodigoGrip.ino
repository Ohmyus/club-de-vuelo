#include "Joystick.h"
#include <Wire.h>

#define encoderAddress  0x36 //Defautl address of the AS5600 magnetic encoder, don't know yet how to change it
#define muxAddress 0x70
#define register_1 0x0C
#define register_2 0X0D

unsigned int lowbyte0, highbyte0, rawAngle0;
unsigned long initTime, deltaTime;

bool debug;

int X, Y;

byte outputPins[5] = {5,6,7,8,9};
byte inputPins[5] = {18,15,14,16,10};
//Declaring Buttons and matrix
  int buttonID = 0;
  const int cols = 5;
  const int rows = 5;
  const int numButtons = rows*cols;
  int lastButtonState[numButtons];
  int currentButtonState[numButtons];

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK , 25, 0,
  true, true, false, false, false, false,
  false, false, false, false, false);

const bool initAutoSendState = true;

void setup () {
  pinMode(1, INPUT_PULLUP);   //prepare debug button
  Wire.begin();               //Start I2C connection
  Wire.setClock(400000);      //set I2C bus frequency to maximum
  Joystick.begin();           //Initialize joystick library - get the arduino to act as HID.
  for (int i = 0; i<5; i++) { //get the pins for the matrix ready
    pinMode(outputPins[i], OUTPUT);
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  Joystick.setXAxisRange(1929,2333);
  Joystick.setYAxisRange(1668,2061);
  if (!digitalRead(1) == true) {  //to enter debug mode, hold button while plugging the arduino in
    debug = true;
    Serial.begin(115200);
    while(!Serial);
    Serial.println("setup complete");
  }
}

void loop () {
  initTime = millis(); //start timer for debug purposes
  //Axis runtime
  X = getAngle(1);
  Y = getAngle(0);
  Joystick.setXAxis(X);
  Joystick.setYAxis(Y);
  //matrix runtime
  matrixRuntime();
  //time calculation and outputs
  if (debug == true) {
    Serial.print("X = ");
    Serial.print(X);
    Serial.print(" | Y = ");
    Serial.print(Y);
    deltaTime = millis() - initTime;
    Serial.print(" | deltaTime = ");
    Serial.println(deltaTime);
  }
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

int getAngle(int channel) {
  Wire.beginTransmission(muxAddress);
  Wire.write(1 << channel);
  Wire.endTransmission();
  // --- request highbyte ---
  Wire.beginTransmission(encoderAddress);
  Wire.write(register_1);
  Wire.endTransmission();

  Wire.requestFrom(encoderAddress, 1);
  if(Wire.available() <= 1) {
    highbyte0 = Wire.read();
  }
  // --- request lowbyte ---
  Wire.beginTransmission(encoderAddress);
  Wire.write(register_2);
  Wire.endTransmission();

  Wire.requestFrom(encoderAddress, 1);
  if(Wire.available() <= 1 ) {
    lowbyte0 = Wire.read();
  }
  highbyte0 = highbyte0 << 8;

  return highbyte0 | lowbyte0;
}
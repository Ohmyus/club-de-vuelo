// slave side code

int buttons = 0;
unsigned long potentiometer = 0;
int buttonPins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,14,15};
int potPin = A2;
int aux;
unsigned long headstate;

#include <Wire.h> 

void setup() { 
  Serial.begin(9600);
  Wire.begin(2);                // join i2c bus with address #2 
  Wire.onRequest(requestEvent); // declaration of handler function 
  for (int i = 0; i < 15; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(potPin, INPUT);
} 

void loop() { 
  for (int i = 0; i < 15; i++) {
    aux = 1 - digitalRead(buttonPins[i]);
    bitWrite(buttons, i, aux);
    delayMicroseconds(10);
  }
  potentiometer = analogRead(potPin);
  headstate = buttons | potentiometer << 22;
  Serial.print(potentiometer);
  Serial.print("|");
  Serial.println(headstate, BIN);
  delay(100);
} 

// function that executes whenever data is received from master 
// this function is registered as an event, see setup() 
void requestEvent() {
  byte message[4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      bitWrite(message[i], j, bitRead(headstate, 8*i + j));
    }
  }
    Wire.write(message, sizeof(message));
}
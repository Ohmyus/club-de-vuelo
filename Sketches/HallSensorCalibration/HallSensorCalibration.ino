#include <Servo.h>

int claw1, claw2, claw3, claw4;
int chance = 20;

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

void setup() {
  myservo1.attach(3);
  myservo2.attach(5);
  myservo3.attach(6);
  myservo4.attach(9);

}

void loop() {
  if (random(0,chance) < 2) {
    toggleServo1();
  }
  if (random(0,chance) < 2) {
    toggleServo2();
  }
  if (random(0,chance) < 2) {
    toggleServo3();
  }
  if (random(0,chance) < 2) {
    toggleServo4();
  }
  delay(500);
}

void toggleServo1() {
  if (claw1 == 1) {
    claw1 = 0;
  }
  else {
    claw1 = 1;
  }
  myservo1.write(100 + 45*claw1);
}

void toggleServo2() {
  if (claw2 == 1) {
    claw2 = 0;
  }
  else {
    claw2 = 1;
  }
  myservo2.write(100 + 45*claw2);
}

void toggleServo3() {
  if (claw3 == 1) {
    claw3 = 0;
  }
  else {
    claw3 = 1;
  }
  myservo3.write(100 + 45*claw3);
}

void toggleServo4() {
  if (claw4 == 1) {
    claw4 = 0;
  }
  else {
    claw4 = 1;
  }
  myservo4.write(100 + 45*claw4);
}


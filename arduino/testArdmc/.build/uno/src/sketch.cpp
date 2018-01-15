#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
//tests the motor control circuit-- drives forward, then side to side, then backward
const int tleft = 8; 
const int tright = 7;
const int forward = 11;
const int backward = 10;

void setup() {
  pinMode(tleft, OUTPUT);
  pinMode(tright, OUTPUT);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
}

void loop() {
  delay(4000);
  digitalWrite(forward, HIGH);
  delay(1000);
  digitalWrite(forward, LOW);
  delay(1000);
  digitalWrite(tleft, HIGH);
  delay(1000);
  digitalWrite(tleft, LOW);
  digitalWrite(tright, HIGH);
  delay(1000);
  digitalWrite(tright, LOW);
  delay(2000);
  digitalWrite(backward, HIGH);
  delay(500);
  digitalWrite(backward, LOW);
  delay(5000);
}

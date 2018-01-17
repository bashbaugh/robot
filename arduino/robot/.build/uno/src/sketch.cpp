#include <Arduino.h>

void setup();
void flash(int n);
void loop();
#line 1 "src/sketch.ino"
#define CMD_READY 224
#define CMD_SHUTDOWN 220 
#define CMD_FORWARD 2
#define CMD_BACKWARD 1
#define CMD_STOP 0
const byte led = 13;
const byte forward = 11;
const byte backward = 10;
const byte left = 6;
const byte right = 7;
boolean ledstate = 0;
int code = 150;
byte pwm = 0;


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
}

void flash(int n) {
  for(int i=0;i<n;i++) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}

void loop() {
  if(Serial.available()) {
    code = Serial.read();
    Serial.flush();
  //  Serial.println(code);
  }
  if(code == CMD_READY) {
    digitalWrite(led, HIGH);
  }
  if(code < 100 && code > 50) {
    digitalWrite(backward, LOW);
    byte pwm = map(code, 50, 100, 0, 225);
    Serial.println(pwm);
    analogWrite(forward, pwm);
  }
  if(code > 0 && code < 50) {
    digitalWrite(forward, LOW);
    pwm = map(code, 50, 0, 0, 225);
    Serial.println(pwm); 
    analogWrite(backward, pwm);
  }
  if(code == 100) {digitalWrite(backward, LOW); digitalWrite(forward, HIGH);}
  if(code == 0) {digitalWrite(forward, LOW); digitalWrite(backward, HIGH);}
  if(code == 50) {
    digitalWrite(forward, LOW);
    digitalWrite(backward, LOW);
  }
  if(code == 151) {digitalWrite(left, LOW); digitalWrite(right, LOW);}
  if(code < 151 && code >= 101) {digitalWrite(right, LOW); digitalWrite(left, HIGH); Serial.println("left");}
  if(code <= 201 && code > 151) {digitalWrite(left, LOW); digitalWrite(right, HIGH); Serial.println("right");}
//if(code == CMD_FORWARD) {
// digitalWrite(backward, LOW);
// digitalWrite(forward, HIGH); 
//}
//if(code == CMD_BACKWARD) {
//digitalWrite(forward, LOW);
//digitalWrite(backward, HIGH);
//}
//if(code == CMD_STOP) {
//  digitalWrite(forward, LOW);
//  digitalWrite(backward, LOW);
//}
  delay(15);
}
  

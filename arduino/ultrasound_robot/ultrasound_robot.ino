//a ultrasound obstacle-avoiding robot
const int tleft = 8; 
const int tright = 7;
const int forward = 11;
const int backward = 10;
const int trig = A0;
const int echo = A1;
const int led = 13;
long duration;
int distance;
boolean was_obstacle = 0;

void setup() {
  pinMode(tleft, OUTPUT);
  pinMode(tright, OUTPUT);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(5000);
  digitalWrite(led, HIGH);
  analogWrite(forward, 110);
}

int getDist() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  return duration*0.034/2;
}

void stopm() {
  digitalWrite(forward, LOW);
  digitalWrite(backward, LOW);
  digitalWrite(tleft, LOW);
  digitalWrite(tright, LOW);
}

void loop() {
  distance = getDist();
  if (distance < 30) {
    stopm();
    digitalWrite(backward, HIGH);
    delay(400);
    digitalWrite(backward, LOW);
    delay(500);
    digitalWrite(tleft, HIGH);
    delay(100);
    digitalWrite(forward, HIGH);
    delay(700);
    stopm();
    delay(500);
    was_obstacle = 1;
    return;
  }
  analogWrite(forward, 150);
}

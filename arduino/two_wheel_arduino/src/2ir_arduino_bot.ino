const byte left_forward = 11;
const byte left_backward = 10;
const byte right_forward = 6;
const byte right_backward = 5;
const byte ir_right = 2; 
const byte ir_left = 12;
const byte led = 13;

bool justTurnedLeft, justTurnedRight;
byte code = 50;
int leftMotorOutput, rightMotorOutput;
byte currXcode = 210;
byte currYcode = 210;

#define FULL 225
#define ZERO 0
#define HALF 115
#define CMD_READY 224
#define CONVERTED_CMD_FORWARD 50
#define CONVERTED_CMD_BACKWARD -50
#define MOTOR_MAX_PWM 225
#define MOTOR_MIN_PWM -225

void flash(int n)
{
  for(int i=0; i<n; i++)
  {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}

void setup(){
  pinMode(led, OUTPUT);
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);
  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);
  flash(2);
  Serial.begin(9600);
}

void calcDiffDrive(float x, float y)
{
  float rawLeft;
  float rawRight;
  //float RawLeft;
  //float RawRight;
	
  float z = sqrt(x * x + y * y); //hypotenuse
  // angle in radians
  float rad = acos(abs(x) / z);

  if (isnan(rad) == true) {
    rad = 0;
  }

  //in degrees
  float angle = rad * 180 / PI;
 
  float tcoeff = -1 + (angle / 90) * 2;
  float turn = tcoeff * abs(abs(y) - abs(x));
  turn = round(turn * 100) / 100;

  float mov = max(abs(y), abs(x));

  if ((x >= 0 && y >= 0) || (x < 0 && y < 0))
  {
    rawLeft = mov; rawRight = turn;
  }
  else
  {
    rawRight = mov; rawLeft = turn;
  }
  if (y < 0) {
    rawLeft = 0 - rawLeft;
    rawRight = 0 - rawRight;
  } 
  leftMotorOutput = map(rawLeft, CONVERTED_CMD_BACKWARD, CONVERTED_CMD_FORWARD, MOTOR_MIN_PWM, MOTOR_MAX_PWM);
  rightMotorOutput = map(rawRight, CONVERTED_CMD_BACKWARD, CONVERTED_CMD_FORWARD, MOTOR_MIN_PWM, MOTOR_MAX_PWM);
}

void stopM()
{
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
  //delay(100);
}

void forward(byte mspeed)
{
  stopM();
  analogWrite(left_forward, mspeed);
  analogWrite(right_forward, mspeed);
}

void backward(byte mspeed)
{
  stopM();
  analogWrite(left_backward, mspeed);
  analogWrite(right_backward, mspeed);
}

void rotateLeft(byte mspeed)
{
  stopM();
  analogWrite(left_backward, mspeed);
  analogWrite(right_forward, mspeed);
}

void rotateRight(byte mspeed)
{
  stopM();
  analogWrite(left_forward, mspeed);
  analogWrite(right_backward, mspeed);
}

void turn(int leftspeed, int rightspeed)
{
  (leftspeed == abs(leftspeed)) ? analogWrite(left_forward, leftspeed) : analogWrite(left_backward, abs(leftspeed));
  (rightspeed == abs(rightspeed)) ? analogWrite(right_forward, rightspeed) : analogWrite(right_backward, abs(rightspeed));
}

void findClearRoute()
{
    byte counter = 0;
    //backward(HALF);
    delay(500);
    while(!digitalRead(ir_left) || !digitalRead(ir_right)){
      rotateLeft(HALF);
      delay(50);
      counter++;
      if(counter>=200){
        while(!digitalRead(ir_left) && !digitalRead(ir_right)){
          rotateRight(HALF);
        } 
        return;
      }
    }
}

void avoidObstacles()
{
  justTurnedRight = justTurnedLeft = false;
  //forward(FULL);
  delay(50);
  if(!digitalRead(ir_right) && !digitalRead(ir_left)){
    findClearRoute();    
  }

  while(!digitalRead(ir_left)){
    rotateRight(FULL);
    delay(50);
    justTurnedRight = true;
  }
  if (justTurnedRight){rotateRight(HALF); delay(400);}
  while(!digitalRead(ir_right)){
    rotateLeft(FULL);
    delay(50);
    justTurnedLeft = true;
  } 
  if(justTurnedLeft){rotateLeft(HALF); delay(400);}
  if(justTurnedLeft && justTurnedRight){
    findClearRoute();
  }

}

void processMovement()
{ 
  //flash(1);
  if(currXcode != 210 && currYcode != 210){
    calcDiffDrive(currXcode - 50, currYcode - 151);
    currXcode = currYcode = 210;
    turn(leftMotorOutput, rightMotorOutput);
  }
  if(code >= 0 && code <= 100){currXcode = code;}
  if(code >= 101 && code <= 201) {currYcode = code;}
}

byte x;
void loop()
{ 
  code = 210;
  avoidObstacles();  
  if(Serial.available() > 0) {
    code = Serial.read();
    //Serial.flush();
    //while(Serial.available() > 0){x = Serial.read();}
  }
  //if(code == CMD_READY)
  //{
  //  flash(1);
  //}

  if(code == 151) {currXcode = currYcode = 210; stopM();} else if(code >= 0 && code <= 201) {processMovement();}
  delay(5);  
}


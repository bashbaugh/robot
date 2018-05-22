const byte left_forward = 11;
const byte left_backward = 10;
const byte right_forward = 6;
const byte right_backward = 5;
const byte ir_right = 2; 
const byte ir_left = 12;

bool justTurnedLeft = false;
bool justTurnedRight = false;

#define FULL 225
#define ZERO 0
#define HALF 115

void setup(){
  pinMode(13, OUTPUT);
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);
  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);
  digitalWrite(13, HIGH);
  //switch(MCUSR) {
 // case 2:
//	   delay(5000);
 //   case 7:
 //          while(true){delay(60000);}
 //   default:
	   delay(10000);
 // } 
 // MCUSR = 0;
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

void loop()
{
  justTurnedRight = justTurnedLeft = false;
  forward(FULL);
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


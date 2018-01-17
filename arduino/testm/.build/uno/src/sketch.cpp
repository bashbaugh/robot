#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
#define pin 6
void setup()
{
pinMode(pin, OUTPUT);
}

void loop()
{
digitalWrite(pin, HIGH);
delay(2000);
}

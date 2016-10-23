#include "StopWatch.h"

StopWatch timeElapsed;
int sensePin1 = 2;
int sensePin2 = 3;
boolean isStarted = false;
int speedLimit = 2000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensePin1, INPUT);
  pinMode(sensePin2, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(sensePin1))
  {
    timeElapsed.start();
    isStarted = true;
    Serial.println("sensed 1");
  }

  if(isStarted)
  {
    if(digitalRead(sensePin2))
    {

      Serial.println("sensed 2");
      timeElapsed.stop();
      Serial.println(timeElapsed.elapsed());

      if(timeElapsed.elapsed() > speedLimit)
        Serial.println("Normal Drive");
      else
        Serial.println("Over speeding");
        delay(1000);
       timeElapsed.reset();
    }
         
  }
  
  
}

#include "StopWatch.h"
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

const int trigPin = 3;
const int echoPin = 4;
// Variables for the duration and the distance
long duration;
int distance,cms;
int safeDistance = 10;
int isTimerStarted = false, isCarNear = false;
int timeLimit = 3000;
int BuzzerPin = 2;

StopWatch timer;
char auth[] = "ce9e7a07e0bd46db9d60e6de405d3925";
WidgetLCD accidentLCD(V0);
WidgetLCD notifyLCD(V1);

void setup() {
  Blynk.begin(auth);
  while (Blynk.connect() == false) {
     //Wait until connected
  }
// put your setup code here, to run once:
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(BuzzerPin, OUTPUT);
Serial.begin(9600);
}


void loop() {
  Blynk.run();
// put your main code here, to run repeatedly:
delay(30);
distance = calculateDistance();
//Serial.print(distance); // Sends the distance value into the Serial Port
//Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing

 if(distance <= safeDistance && !isCarNear && distance != 1)
 {
    Serial.println("Car is Near");
    isCarNear = true;
    Serial.println(distance);
 }

 if(distance > safeDistance)
 {
      timer.reset();
      isCarNear = false;
      isTimerStarted = false; 
      digitalWrite(BuzzerPin, LOW);
      accidentLCD.clear();
      accidentLCD.print(4,0,"NONE");
      notifyLCD.clear();
      notifyLCD.print(4,0,"NONE");
      
 }
  

 if(isCarNear && !isTimerStarted)
 {
  Serial.println("Timer started");
   timer.start();
   isTimerStarted = true;
 }

 if(isTimerStarted)
 {
    if(timer.elapsed() >= timeLimit)
    {
      timer.stop();
      timer.reset();
      Serial.println("Accident occured");
      accidentLCD.clear();
      accidentLCD.print(4,0,"Accident");
      accidentLCD.print(4,1,"Occured");
      notifyLCD.clear();
      notifyLCD.print(4 ,0,"Do u need");
      notifyLCD.print(4,1,"Assistance?");
      digitalWrite(BuzzerPin, HIGH);
      isCarNear = false;
      isTimerStarted = false;      
    }
 }
}


int calculateDistance(){ 
 
digitalWrite(trigPin, LOW); 
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
distance= (duration/2) / 74; 
// distance= duration*0.034/2;
// cm = (duration/2) / 29.1;
return distance;
}


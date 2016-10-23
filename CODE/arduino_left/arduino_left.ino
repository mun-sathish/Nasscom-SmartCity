#include <Servo.h>
#include "StopWatch.h"
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>


const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 4;
long duration;
int distance, cms;
Servo myServo;

//--------------------------------------


int isHumanDetected_1 = false;
int isHumanDetected_2 = false;
int ledPin1 = 5;
int ledPin2 = 6;

//-------------------------------------

StopWatch timeElapsed;
int sensePin1 = 7;
int sensePin2 = 8;
boolean isStarted = false;
int speedLimit = 1500;

//--------------------------------------

char auth[] = "ce9e7a07e0bd46db9d60e6de405d3925";
WidgetLCD carParkingLCD(V0);
WidgetLCD speedAlertLCD(V1);
WidgetLED lamp1(V2);
WidgetLED lamp2(V3);

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth);
  while (Blynk.connect() == false) {
    // Wait until connected
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  pinMode(sensePin1, INPUT);
  pinMode(sensePin2, INPUT);


}

void loop() {
  Blynk.run();
  servo_function();
  //human_detection();
  //speed_vehicles();
}

void speed_vehicles()
{

  if (digitalRead(sensePin1))
  {
    timeElapsed.start();
    isStarted = true;
    Serial.println("sensed 1");
  }

  if (isStarted)
  {
    if (digitalRead(sensePin2))
    {
      Serial.println("sensed 2");
      timeElapsed.stop();
      Serial.println(timeElapsed.elapsed());
      speedAlertLCD.clear();

      if (timeElapsed.elapsed() > speedLimit)
        speedAlertLCD.print(2, 0, "Normal Drive");
      else
        speedAlertLCD.print(2, 0, "Over Speeding");
      isStarted = false;
      timeElapsed.reset();
    }

  }
}

void human_detection()
{
  isHumanDetected_1  = digitalRead(sensePin1);
  isHumanDetected_2  = digitalRead(sensePin2);
  //  Serial.println(digitalRead(humanDetectionPin));
  if (isHumanDetected_1)
  {
    digitalWrite(ledPin1, HIGH);
    //    lamp1.on();
  }
  else
  {
    digitalWrite(ledPin1, LOW);
    //    lamp1.off();
  }

  if (isHumanDetected_2)
  {
    digitalWrite(ledPin2, HIGH);
    //    lamp2.on();
  }
  else
  {
    digitalWrite(ledPin2, LOW);
    //    lamp2.off();
  }
}

void servo_function()
{
  for (int i = 15; i <= 165; i += 10)
  {
    myServo.write(i);
    delay(300);
    distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

    Serial.print(i); // Sends the current degree into the Serial Port
    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); // Sends the distance value into the Serial Port
    Serial.println("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }

  for (int i = 165; i > 15; i -= 10)
  {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    // Serial.print(i);
    //Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  if (distance >= 10)
  {
    carParkingLCD.clear();
    carParkingLCD.print(4, 0, "Parking Bay");
    carParkingLCD.print(4, 1, "Available");
  }
  else
  {
   
    carParkingLCD.clear();
    carParkingLCD.print(4, 0, "Not");
    carParkingLCD.print(4, 1, "Available");
  
  }
}

int calculateDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  // cm = (duration/2) / 29.1;
  return distance;
}


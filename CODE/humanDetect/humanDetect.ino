int humanDetectionPin = 2;
int isHumanDetected = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(humanDetectionPin, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  isHumanDetected  = digitalRead(humanDetectionPin);

  Serial.println(digitalRead(humanDetectionPin));
  
  if(isHumanDetected)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  
}

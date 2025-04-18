#include <Servo.h>

Servo myservo;  

const int stopPin = 12;  
const int manualPin = 2;
const int buzzerPin = 8;
const int potPin = A5;
const int greenPin = 3;
const int yellowPin = 5;
const int redPin = 6;

bool checkConditions = false;



void setup() {
  myservo.attach(9);
  
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(manualPin, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{

  for (int pos = 0; pos <= 170; pos += 25)
  {
    if(digitalRead(stopPin) == LOW || digitalRead(manualPin) == LOW)
    {
      checkConditions = true;
      break;
    }

    analogWrite(greenPin, 10);
    myservo.write(pos);
    delay(500);
    analogWrite(greenPin, 0);

    delay(5000);
  }


  for (int pos = 170; pos >= 0; pos -= 25)
  {
    if(digitalRead(stopPin) == LOW || digitalRead(manualPin) == LOW || checkConditions == true)
    {
      break;
    }

    analogWrite(greenPin, 10);
    myservo.write(pos);
    delay(500);
    analogWrite(greenPin, 0);

    delay(5000);
  }

  if(digitalRead(manualPin) == LOW)
  {
    manualMode();
  }

  if(digitalRead(stopPin) == LOW)
  {
    stopMode();
  }

}

void manualMode()
{
  tone(buzzerPin, 1000);
  delay(200);
  noTone(buzzerPin);


  while (digitalRead(manualPin) == LOW) 
  {
    analogWrite(yellowPin, 100);
    int potValue = analogRead(potPin);
    int servoPos = map(potValue, 0, 1023, 0, 170);
    myservo.write(servoPos);
    delay(2000);
    analogWrite(yellowPin, 0);
    delay(500);
  }
  
  checkConditions = false;
  
  tone(buzzerPin, 500);
  delay(200);
  noTone(buzzerPin);
}

void stopMode()
  {
    analogWrite(redPin, 100);

    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    
    
myservo.write(0);
    delay(500);
    myservo.detach(); 

    analogWrite(redPin, 0);

    while (digitalRead(stopPin) == LOW) 
    {
      delay(5000);
      analogWrite(redPin, 100);
      delay(200);
      analogWrite(redPin, 0);
    }

    tone(buzzerPin, 500);
    delay(200);
    noTone(buzzerPin);

    checkConditions = false;
    myservo.attach(9);

  }

#include <ArduinoJson.h>

#define trigPin 10
#define echoPin 9

int counter;
float duration;
float distance;
unsigned long time;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = 0;
  counter = 0;
  while (--counter != 0) 
  {
    if (PINB & 2) 
    {
      time = micros();
      break;
    }
  }
  while (--counter != 0) 
  {
    if ((PINB & 2) == 0) 
    {
      duration = micros() - time;
      break;
    }
  }

  distance = (duration / 2) * 0.0344;

  StaticJsonDocument<100> json; // Tamanho do buffer para o JSON

  if (distance > 400) 
  {
    json["distance"] = "> 400";
  } 
  else if (distance < 2) 
  {
    json["distance"] = "< 2";
  } 
  else 
  {
    json["distance"] = distance;
  }

  String jsonString;
  serializeJson(json, jsonString);
  
  Serial.println(jsonString); // Envia o JSON via serial

  delay(1000);
}

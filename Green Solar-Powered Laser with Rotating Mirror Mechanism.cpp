#include <Arduino.h>
#include <ESP32Servo.h> 

Servo myservo;      
Servo secondServo;   

#define LDR 27
#define laser 14

unsigned long lowDelay = 3600000;

const int potPin = 15;  
const int servoPin = 13; 
const int secondServoPin = 12; 

void setup() {
  myservo.attach(servoPin);          
  secondServo.attach(secondServoPin);  
  secondServo.write(0); 
  pinMode(LDR, INPUT); 
  pinMode(laser, OUTPUT);             

  Serial.begin(9600); 
  Serial.println("System is UP and Running");
}

void loop() {
  int potValue = analogRead(potPin);          
  int angle = map(potValue, 0, 4095, 0, 180); 
  
  myservo.write(angle);  
  delay(15); 

  int lightState = digitalRead(LDR);

  if (lightState == HIGH) {
    Serial.println("No Light Detected");
    Serial.println("Timer Stoped");
  } 
  
  else {
    Serial.println("Light Detected");
    Serial.println("Timer Running");
    digitalWrite(laser, HIGH);
    delay(300000); 
    digitalWrite(laser, LOW); 
    delay(lowDelay); 
    lowDelay += 300000;
  }
}
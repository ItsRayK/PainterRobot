#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define IR1 A2
#define IR2 A3
#define LIMUP 5
#define LIMDOWN 6

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motorLeft = AFMS.getMotor(1);
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorPaint = AFMS.getMotor(3);

int dir = 0; // Current Vertical Direction: 0=DOWN ; 1=UP

void setup() {
  Serial.begin(9600);

  Serial.println("Painter Robot is starting up...");
  AFMS.begin();
  delay(500);

  Serial.println("Setting up digital devices...");
  pinMode(LIMUP, INPUT_PULLUP);
  pinMode(LIMDOWN, INPUT_PULLUP);
  
  Serial.println("Setting initial motor speeds...");
  motorLeft->setSpeed(30);
  motorRight->setSpeed(30);
  motorPaint->setSpeed(30);
  delay(800);
  
  Serial.println("Releasing all motors...");
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorPaint->run(RELEASE);
  delay(100);
  
  Serial.println("Painter Robot initialization complete!");
  delay(100);
  Serial.println("Running main loop...");
}

void loop() {
  

  
}

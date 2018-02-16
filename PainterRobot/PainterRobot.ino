/*
   Title: Painter Robot (for AE-ME 3703) C-Term

   Description: This is code for a painter robot designed to paint a
    a vertical wall. The robot should approach the wall, paint and
    keep consistent pressure of the paint roller to the wall.

    An IR sensor controls the distance to keep between the robot and
    the given wall.
    Limit Switches are used to control the winch motor that raises
    and lowers the roller.
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define IR1 A2

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

  Serial.println("Setting up GPIO pins...");
  pinMode(LIMUP, INPUT_PULLUP);
  pinMode(LIMDOWN, INPUT_PULLUP);

  Serial.println("Setting initial motor speeds...");
  motorLeft->setSpeed(30);
  motorRight->setSpeed(30);
  motorPaint->setSpeed(150);
  delay(800);

  Serial.println("Releasing all motors...");
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorPaint->run(RELEASE);
  delay(500);

  Serial.println("Painter Robot initialization complete!");
  delay(700);
  Serial.println("Running main loop...");
}

void loop() {
  approachWall(600);
  paint();
}

//Painting Code
void paint() {
  int topSwitch = digitalRead(LIMUP);
  int botSwitch = digitalRead(LIMDOWN);

  if (topSwitch == 1 && dir == 1) {
    dir = 0;
  }

  else if (botSwitch == 1 && dir == 0) {
    dir = 1;
  }

  if (dir == 1) {
    motorPaint->setSpeed(100);
    motorPaint->run(FORWARD);
  }

  else if (dir == 0) {
    motorPaint->setSpeed(150);
    motorPaint->run(BACKWARD);
  }
}

//Driving Code
void approachWall(int dist) {
  float pk = 1.5; //Basic proportional control
  float realDist = analogRead(IR1);
  Serial.print(realDist);
  Serial.print("    ");
  float error = realDist - dist;
  error = error * pk;
  drive(error);
  Serial.println(error);
}

void drive(int spd) {
  if (spd > 0) {
    motorLeft->setSpeed(abs(spd));
    motorRight->setSpeed(abs(spd));

    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
  else if (spd <= 0) {
    motorLeft->setSpeed(abs(spd));
    motorRight->setSpeed(abs(spd));

    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
  }
}


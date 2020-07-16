// gauge.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "gauge.h"


Gauge::Gauge(unsigned int motor_steps, unsigned int min_angle, unsigned int max_angle, int pin_1, int pin_2, int pin_3, int pin_4)
: kMotorSteps(motor_steps)
, kMinAngle(min_angle)
, kMaxAngle(max_angle)
, stepper(motor_steps, pin_1, pin_2, pin_3 ,pin_4)
{ }


void Gauge::Initialize(unsigned int motorRPM) {
  // Set motor speed - Speed is RPM * 2
  stepper.setSpeed(motorRPM * 2);
  
  // Return motor to home position.
  stepper.step(-kMotorSteps);
}


void Gauge::SetPercentage(unsigned int percentage) {
  // Safeguard against percentages over 100 by capping.
  if (percentage > 100) {
    percentage = 100;
  }
  
  unsigned int currentPercentage = (position * 100) / kMotorSteps;
  int percentageDifference = percentage - currentPercentage;
  int stepsDifference = (percentageDifference / 100 ) * kMotorSteps;
  stepper.step(stepsDifference);
  position = position + stepsDifference;
}


void Gauge::SetAngle(unsigned int angle) {
  // Safeguard against angles over maxAngle by capping.
  if (angle > kMaxAngle) {
    angle = kMaxAngle;
  }

  // Safeguard against angles under minAngle by capping.
  if (angle < kMinAngle) {
    angle = kMaxAngle;
  }

  int totalAngles = kMaxAngle - kMinAngle;
  
  unsigned int currentAngle = (position * totalAngles) / kMotorSteps;
  int angleDifference = angle - currentAngle;
  int stepsDifference = (angleDifference / kMaxAngle) * kMotorSteps;
  stepper.step(stepsDifference);
  position = position + stepsDifference;
}

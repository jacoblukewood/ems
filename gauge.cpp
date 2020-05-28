// Copyright 2020 Jacob Wood

#include "gauge.h"


Gauge::Gauge(unsigned int kMotorSteps, unsigned int kMinAngle, unsigned int kMaxAngle, int kPin1, int kPin2, int kPin3, int kPin4) : kMotorSteps(kMotorSteps), kMinAngle(kMinAngle), kMaxAngle(kMaxAngle), stepper(kMotorSteps, kPin1, kPin2, kPin3 ,kPin4) {
}

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
  
  int currentPercentage = (position * 100) / kMotorSteps;
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
  
  int currentAngle = (position * totalAngles) / kMotorSteps;
  int angleDifference = angle - currentAngle;
  int stepsDifference = (angleDifference / kMaxAngle) * kMotorSteps;
  stepper.step(stepsDifference);
  position = position + stepsDifference;
}

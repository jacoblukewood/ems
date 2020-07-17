// gauge.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "gauge.h"

Gauge::Gauge(unsigned int const motor_steps, unsigned int const stepper_rpm, unsigned int const min_angle, unsigned int const max_angle, unsigned int const pin_1, unsigned int const pin_2, unsigned int const pin_3, unsigned int const pin_4)
: kMotorSteps(motor_steps)
, kStepperRPM(stepper_rpm)
, kMinAngle(min_angle)
, kMaxAngle(max_angle)
, stepper(motor_steps, pin_1, pin_2, pin_3 ,pin_4) {
  // Set motor speed - Speed is RPM * 2
  stepper.setSpeed(kStepperRPM * 2);
  
  // Return motor to home position.
  stepper.step(-kMotorSteps);
}


void Gauge::SetPercentage(unsigned int percentage) {
  // Safeguard against percentages over 100 by capping.
  if (percentage > 100) {
    percentage = 100;
  }
  
  unsigned int currentPercentage = (current_position_ * 100) / kMotorSteps;
  int percentageDifference = percentage - currentPercentage;
  int stepsDifference = (percentageDifference / 100 ) * kMotorSteps;
  stepper.step(stepsDifference);
  current_position_ += stepsDifference;
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
  
  unsigned int currentAngle = (current_position_ * totalAngles) / kMotorSteps;
  int angleDifference = angle - currentAngle;
  int stepsDifference = (angleDifference / kMaxAngle) * kMotorSteps;
  stepper.step(stepsDifference);
  current_position_ += stepsDifference;
}

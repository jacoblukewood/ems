// Copyright 2020 Jacob Wood

#include "motorcycle.h"

#include <Arduino.h>

#include "utility.h"

Motorcycle::Motorcycle(void)
: horn_(kPinOutputHorn)
, button_brake_(kPinInputButtonRearBrake, &light_tail_)
, button_highbeam_(kPinInputButtonHighBeam, &light_headlight_)
, button_horn_(kPinOutputHorn, &horn_)
, button_indicator_left_(kPinInputButtonIndicatorLeft, 300, &indicator_left_, &indicator_right_)
, button_indicator_right_(kPinInputButtonIndicatorLeft, 300, &indicator_right_, &indicator_left_)
, display_dash_(0x3C, Adafruit128x64)
, engine_(kTachometerRedline, kTachometerRunningMinimum, kTimeoutCranking, kPinInputSensorTachometer, kPinOutputPoints, kPinOutputStarterMotor)
, gauge_dash_(kGaugeDashStepperMotorSteps, kGaugeDashStepperMotorRPM, kGaugeDashMinAngle, kGaugeDashMaxAngle, kPinGaugeDash1, kPinGaugeDash2, kPinGaugeDash3, kPinGaugeDash4)
, indicator_left_(kFlashRate, kPinOutputIndicatorLeft)
, indicator_right_(kFlashRate, kPinOutputIndicatorRight)
, light_headlight_(kPinOutputHeadlight)
, light_tail_(kPinOutputTailLight)
, odometer_(kEEPROMOdometerAddress)
, rfid_reader_(kPinInputPinSS, kPinInputRST)
, sensor_neutral_(kPinInputSensorNeutral)
, sensor_speed_(kPinInputSensorSpeed)
, side_stand_(kPinInputSensorSideStand)
{ }

// Switches on permenant power and records start time.
// Equivalent to entering the accessory power mode in a car from off.
void Motorcycle::PowerOn(void) {
    digitalWrite(kPinElectronicsPower, HIGH);
    SetPowerOnTime(millis());
}

// Switches off permenant power, resets components, and saves the odometer.
// Equivalent to entering the off power mode in a car.
void Motorcycle::PowerOff(void) {
    odometer_.SaveOdometerToEEPROM();
    digitalWrite(kPinElectronicsPower, LOW);
}

bool Motorcycle::IsPoweredOn(void) const {
    return digitalRead(kPinElectronicsPower);
}

// Returns the state of the motorcycles safety sensors.
// true: safety sensor is active, motorcycle is unsafe.
// false: safety sensors are not active, motorcycle is safe.
bool Motorcycle::IsSafeToRide(void) const {
    return side_stand_.IsLowered();
}

// Returns the current speed of the motorcycle in km/h.
unsigned int Motorcycle::GetSpeed(void) const {
    // TODO: Add adjustment settings.
    return utility::IsDigitalInputHigh(kPinInputSensorSpeed);
}

// Returns the current distance of the motorcycles odometer in km.
unsigned int Motorcycle::GetOdometer(void) const {
    // TODO: Implement
    return 0;
}

unsigned int Motorcycle::GetPowerOnTime(void) const {
    return power_on_time_;
}

unsigned int Motorcycle::GetAccessoryModeTimeout(void) const {
    return kAccessoryModeTimeout;
}

unsigned int Motorcycle::GetTimeAccessoryModeStarted(void) const {
 return time_accessory_mode_started_;
}

unsigned int Motorcycle::SetTimeAccessoryModeStarted(unsigned int time) {
    time_accessory_mode_started_ = time;
}

void Motorcycle::SetPowerOnTime(int new_time_value) {
    power_on_time_ = new_time_value;
}

void Motorcycle::RefreshButtons(void) {
  button_brake_.Refresh();
  button_highbeam_.Refresh();
  button_horn_.Refresh();
  button_indicator_left_.Refresh();
  button_indicator_right_.Refresh();
}

// // Returns the difference that the motorcycle has changed in speed in a period > 1 second.
// static unsigned int Motorcycle::SpeedComparison(void) const {
//     static unsigned int speed_last_recorded_;
//     static unsigned int time_last_recorded_;
//     double difference;

//     if (utility::IntervalPassed(time_last_recorded_, 1000)) {
//         difference = Motorcycle::GetSpeed() * ((millis() - time_last_recorded_) / 1000);

//         speed_last_recorded_ = Motorcycle::GetSpeed();
//         time_last_recorded_ = millis();
//     }

//     return difference;
// }

// // Checks if the motorcycle is slowing and activates the brake lights accordingly.
// void Motorcycle::AutoBrakeLight(void) {
//     if ((Motorcycle::GetSpeed() < 2) || Motorcycle::SpeedComparison() > kAutoBrakeDecelerationRate) {
//         Motorcycle::light_tail_.SetLock(false);  // Stop recording the state of the motorcycle brakes. TODO: Modify the button check function to only run if this is false.
//         Motorcycle::light_tail_.SetState(HIGH);
//         Motorcycle::light_tail_.SetLock(true);
//     } else {
//         Motorcycle::light_tail_.SetLock(false);
//     }
// }

// // Checks if the motorcycle is slowing rapidly and strobes the brake lights to warn of danger.
// void Motorcycle::EmergencyBrakeStrobe(void) {
//     // more than 15/km drop in 1 second
//     static unsigned int time_last_cycled_;

//     if (Motorcycle::SpeedComparison() > kEmergencyBrakeDecelerationRate) {
//         if (utility::IntervalPassed(time_last_cycled_, kTailLightStrobeInterval)) {
//             Motorcycle::light_tail_.SetLock(false);
//             Motorcycle::light_tail_.SetState(!light_tail_.GetState());
//             Motorcycle::light_tail_.SetLock(true);  // Stop recording the state of the motorcycle brakes. TODO: Modify the button check function to only run if this is false.
//         }
//     } else {
//         Motorcycle::light_tail_.SetLock(false);
//     }
// }

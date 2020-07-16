// Copyright 2020 Jacob Wood

#include "motorcycle.h"

#include <Arduino.h>

#include "utility.h"

Motorcycle::Motorcycle() : button_brake_(kPinInputButtonBrake, Button::ButtonTypes::kMomentary, &light_tail_),
                           button_highbeam_(kPinInputButtonHighBeam, Button::ButtonTypes::kToggle, &light_headlight_),
                           button_horn_(kPinInputButtonHorn, Button::ButtonTypes::kMomentary, &horn_),
                           button_indicator_left_(kPinInputButtonIndicatorLeft, Button::ButtonTypes::kToggle, &indicator_left_),
                           button_indicator_right_(kPinInputButtonIndicatorRight, Button::ButtonTypes::kToggle, &indicator_right_),
                           button_power_(kPinInputButtonPower, Button::ButtonTypes::kPower, &engine_),

                           engine_(kTachometerRedline, kTachometerRunningMinimum, kTimeoutCranking, kPinInputSensorTachometer, kPinOutputPoints, kPinOutputStarterMotor),

                           horn_(kPinOutputHorn),

                           indicator_left_(kFlashRate, kPinOutputIndicatorLeft),
                           indicator_right_(kFlashRate, kPinOutputIndicatorRight),

                           light_tail_(kBrightnessTailLight, kBrightnessBrakeLight, kPinOutputTailLight),
                           light_headlight_(kBrightnessHeadlight, kBrightnessHighbeam, kPinOutputHeadlight),

                           odometer_(kEEPROMOdometerAddress),

                           rfid_seat_(kPinInputPinSS, kPinInputRST),

                           sensor_neutral_(kPinInputSensorNeutral),
                           sensor_side_stand_(kPinInputSensorSideStand),
                           sensor_tachometer_(kPinInputSensorTachometer),
                           sensor_speed_(kPinInputSensorSpeed) 
                           side_stand(kPinInputSensorSideStand)
                           {
    display_dash_.Setup();
}

// Switches on permenant power and records start time.
// Equivalent to entering the accessory power mode in a car from off.
void Motorcycle::PowerOn(void) {
    digitalWrite(kPinElectronicsPower, HIGH);
    SetPowerOnTime(millis());
}

// Switches off permenant power, resets components, and saves the odometer.
// Equivalent to entering the off power mode in a car.
void Motorcycle::PowerOff(void) {
    odometer_.SaveOdometer();
    digitalWrite(kPinElectronicsPower, LOW);
}

bool Motorcycle::IsPoweredOn(void) const {
    return digitalRead(kPinElectronicsPower);
}

// Returns the state of the motorcycles safety sensors.
// true: safety sensor is active, motorcycle is unsafe.
// false: safety sensors are not active, motorcycle is safe.
bool Motorcycle::IsSafeToRide(void) const {
    return side_stand.IsLowered();
}

// Returns the current speed of the motorcycle in km/h.
unsigned int Motorcycle::GetSpeed(void) const {
    // TODO: Add adjustment settings.
    return utility::GetPinInputState(kPinInputSensorSpeed);
}

// Returns the current distance of the motorcycles odometer in km.
unsigned int Motorcycle::GetOdometer(void) const {
    // TODO: Implement
    return 0;
}

unsigned int Motorcycle::GetPowerOnTime(void) const {
    return power_on_time_;
}

void Motorcycle::SetPowerOnTime(int new_time_value) {
    power_on_time_ = new_time_value;
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

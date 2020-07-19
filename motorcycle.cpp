// Copyright 2020 Jacob Wood

#include "motorcycle.h"

#include <Arduino.h>

#include "utility.h"

Motorcycle::Motorcycle(void)
: horn_(kPinOutputHorn)
, button_brake_(kPinInputButtonRearBrake, utility::kDefaultDebounce, &light_tail_)
, button_highbeam_(kPinInputButtonHighBeam, utility::kDefaultDebounce, &light_headlight_)
, button_horn_(kPinOutputHorn, utility::kDefaultDebounce, &horn_)
, button_indicator_left_(kPinInputButtonIndicatorLeft, utility::kDefaultDebounce, &indicator_left_, &indicator_right_)
, button_indicator_right_(kPinInputButtonIndicatorLeft, utility::kDefaultDebounce, &indicator_right_, &indicator_left_)
, button_power_(kPinInputButtonPower, utility::kDefaultDebounce, &engine_)
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
// Equivalent to entering the output power mode in a car from off.
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

unsigned int Motorcycle::GetEmergencyStrobeCyclesPerSecond(void) const {
    return kEmergencyStrobeCyclesPerSecond;
}

// Returns the current distance of the motorcycles odometer in km.
unsigned int Motorcycle::GetOdometer(void) const {
    // TODO: Implement
    return 0;
}

unsigned int Motorcycle::GetPowerOnTime(void) const {
    return power_on_time_;
}

unsigned int Motorcycle::GetOutputModeTimeout(void) const {
    return kOutputModeTimeout;
}

unsigned int Motorcycle::GetTimeOutputModeStarted(void) const {
 return time_output_mode_started_;
}

unsigned int Motorcycle::SetTimeOutputModeStarted(unsigned int time) {
    time_output_mode_started_ = time;
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
  button_power_.Refresh();
}

// Returns the difference that the motorcycle has changed in speed in a period ~ 1 second.
double Motorcycle::SpeedDifferenceIn1Second(void) const {
    static unsigned int last_speed_sample;
    static unsigned int time_last_speed_sample_taken = 0; // will this reset to 0 each function call? if so move to class as property.
    double difference;

    if (utility::IntervalPassed(time_last_speed_sample_taken, 1000)) {
        difference = Motorcycle::GetSpeed() * ((millis() - time_last_speed_sample_taken) / 1000);    // Multiply by actual time to account for delay and slighly going over 1 second.

        last_speed_sample = Motorcycle::GetSpeed();
        time_last_speed_sample_taken = millis();
    }

    return difference;
}


bool Motorcycle::IsSlowingDownOrStopped(void) const {
    if(SpeedDifferenceIn1Second() > (-kAutoBrakeDecelerationRate)) {
        return true;
    } else {
        return false;
    }
}


bool Motorcycle::IsBrakingRapidly(void) const {
    if(SpeedDifferenceIn1Second() > (-kEmergencyBrakeDecelerationRate)) {
        return true;
    } else {
        return false;
    }
}

#include "motorcycle.h"

Motorcycle::Motorcycle(Engine const &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kAutoBrakeDecelerationRate, unsigned int const kEmergencyBrakeDecelerationRate, unsigned int const kTailLightStrobeInterval, Display const &display_dash, unsigned int const kPinOutputPower, unsigned int const kPinInputSensorSideStand) : engine_(engine), kPinInputSensorSpeed_(kPinInputSensorSpeed), kAutoBrakeDecelerationRate_(kAutoBrakeDecelerationRate), kEmergencyBrakeDecelerationRate_(kEmergencyBrakeDecelerationRate), kTailLightStrobeInterval_(kTailLightStrobeInterval), display_dash_(display_dash), kPinOutputPower_(kPinOutputPower), kPinInputSensorSideStand_(kPinInputSensorSideStand)
{
}

// Switches on permenant power and records start time.
// Equivalent to entering the accessory power mode in a car from off.
bool Motorcycle::PowerOn(void)
{
    digitalWrite(Motorcycle::kPinOutputPower_, HIGH);
    time_enter_acc_ = millis();
    return true;
}

// Switches off permenant power, resets components, and saves the odometer.
// Equivalent to entering the off power mode in a car.
bool Motorcycle::PowerOff(void)
{
    // TODO: Clear display, return speedo, and save odometer.
    digitalWrite(Motorcycle::kPinOutputPower_, LOW);
    return true;
}

bool Motorcycle::GetStatePower(void) const
{
    return digitalRead(Motorcycle::kPinOutputPower_);
}

// Returns the state (boolean) of the side stand.
// true: stand is engaged.
// false: stand is disengaged.
bool Motorcycle::GetStateSensorSideStand(void) const
{
    return helper::GetInputState(Motorcycle::kPinInputSensorSideStand_);
}

// Returns the state of the motorcycles safety sensors.
// true: safety sensor is active, motorcycle is unsafe.
// false: safety sensors are not active, motorcycle is safe.
bool Motorcycle::GetStateSafety(void) const
{
    return GetStateSensorSideStand();
}

// Returns the current speed of the motorcycle in km/h.
unsigned int Motorcycle::GetSpeed(void) const
{
    // TODO: Add adjustment settings.
    return helper::GetInputState(Motorcycle::kPinInputSensorSpeed_);
}

// Returns the current distance of the motorcycles odometer in km.
unsigned int Motorcycle::GetOdometer(void) const
{
    // TODO: Implement
    return 0;
}

// Returns the difference as a perfentage that the motorcycle has changed in speed in a period > 1 second.
unsigned int Motorcycle::SpeedComparison(void) const
{
    static unsigned int speed_last_recorded_;
    static unsigned int time_last_recorded_;

    if (helper::IntervalPassed(time_last_recorded_, 1000))
    {
        return ((Motorcycle::GetSpeed() / speed_last_recorded_) * ((time_last_recorded_ - millis()) / 1000));
    }
}

// Checks if the motorcycle is slowing and activates the brake lights accordingly.
void Motorcycle::AutoBrakeLight(void)
{
    if ((Motorcycle::GetSpeed() < 1) || Motorcycle::GetSpeed() > kAutoBrakeDecelerationRate_)
    {
        // TODO:
        // Speed less than 2 km compared to 1 second before
        // Motorcycle::brake.SetState(HIGH);
    }
}

// Checks if the motorcycle is slowing rapidly and strobes the brake lights to warn of danger.
void Motorcycle::EmergencyBrakeStrobe(void)
{

    // more than 15/km drop in 1 second
    // static unsigned int time_last_cycled_;

    if (Motorcycle::SpeedComparison() > kEmergencyBrakeDecelerationRate_)
    {
        // TODO:
        // if (time_last_cycled_ > kTailLightStrobeInterval_)
        // {
        //     // Motorcycle::brake.SetState(!break.GetState());
        // }
    }
}
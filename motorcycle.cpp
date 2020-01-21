#include "motorcycle.h"

Motorcycle::Motorcycle(Engine const &engine, Accessory const &light_tail, unsigned int const kPinInputSensorSpeed, unsigned int const kAutoBrakeDecelerationRate, unsigned int const kEmergencyBrakeDecelerationRate, unsigned int const kTailLightStrobeInterval, Display const &display_dash, unsigned int const kPinOutputPower, Sensor const &sensor_side_stand) : engine_(engine), light_tail_(light_tail), kPinInputSensorSpeed_(kPinInputSensorSpeed), kAutoBrakeDecelerationRate_(kAutoBrakeDecelerationRate), kEmergencyBrakeDecelerationRate_(kEmergencyBrakeDecelerationRate), kTailLightStrobeInterval_(kTailLightStrobeInterval), display_dash_(display_dash), kPinOutputPower_(kPinOutputPower), sensor_side_stand_(sensor_side_stand)
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
bool Motorcycle::PowerOff(void) const
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
    return Motorcycle::sensor_side_stand_.GetState();
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

// Returns the difference that the motorcycle has changed in speed in a period > 1 second.
unsigned int Motorcycle::SpeedComparison(void) const
{
    static unsigned int speed_last_recorded_;
    static unsigned int time_last_recorded_;
    double difference;

    if (helper::IntervalPassed(time_last_recorded_, 1000))
    {

        difference = Motorcycle::GetSpeed() * ((millis() - time_last_recorded_) / 1000);

        speed_last_recorded_ = Motorcycle::GetSpeed();
        time_last_recorded_ = millis();
    }

    return difference;
}

// Checks if the motorcycle is slowing and activates the brake lights accordingly.
void Motorcycle::AutoBrakeLight(void)
{
    if ((Motorcycle::GetSpeed() < 2) || Motorcycle::SpeedComparison() > kAutoBrakeDecelerationRate_)
    {
        Motorcycle::light_tail_.SetLock(false); // Stop recording the state of the motorcycle brakes. TODO: Modify the button check function to only run if this is false.
        Motorcycle::light_tail_.SetState(HIGH);
        Motorcycle::light_tail_.SetLock(true);
    }
    else
    {
        Motorcycle::light_tail_.SetLock(false);
    }
}

// Checks if the motorcycle is slowing rapidly and strobes the brake lights to warn of danger.
void Motorcycle::EmergencyBrakeStrobe(void)
{
    // more than 15/km drop in 1 second
    static unsigned int time_last_cycled_;

    if (Motorcycle::SpeedComparison() > kEmergencyBrakeDecelerationRate_)
    {
        if (helper::IntervalPassed(time_last_cycled_, kTailLightStrobeInterval_))
        {
            Motorcycle::light_tail_.SetLock(false);
            Motorcycle::light_tail_.SetState(!light_tail_.GetState());
            Motorcycle::light_tail_.SetLock(true); // Stop recording the state of the motorcycle brakes. TODO: Modify the button check function to only run if this is false.
        }
    }
    else
    {
        Motorcycle::light_tail_.SetLock(false);
    }
}
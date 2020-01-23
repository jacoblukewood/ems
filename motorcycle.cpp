#include "motorcycle.h"

#include <Arduino.h>

#include "helper.h"

Motorcycle::Motorcycle() : engine_(kTimeoutCranking_, kTachometerRunningMinimum_, kTachometerRedline_, kPinOutputPoints_, kPinOutputStarterMotor_, kPinInputSensorTachometer_),
                           odometer_(kEEPROMOdometerAddress_),
                           indicator_left_(kPinOutputIndicatorLeft_, kFlashRate_),
                           indicator_right_(kPinOutputIndicatorRight_, kFlashRate_),
                           light_tail_(kPinOutputTailLight_, kBrightnessTailLight_, kBrightnessBrakeLight_),
                           light_headlight_(kPinOutputHeadlight_, kBrightnessHeadlight_, kBrightnessHighbeam_),
                           horn_(kPinOutputHorn_),

                           rfid_seat_(kPinInputPinSS_, kPinInputRST_), 
                           
                           sensor_neutral_(kPinInputSensorNeutral_),
                           sensor_side_stand_(kPinInputSensorSideStand_),
                           sensor_tachometer_(kPinInputSensorTachometer_),
                           sensor_speed_(kPinInputSensorSpeed_),

                           button_indicator_left_(kPinInputButtonIndicatorLeft_, &indicator_left_, Button::ButtonTypes::kToggle),
                           button_indicator_right_(kPinInputButtonIndicatorRight_, &indicator_right_, Button::ButtonTypes::kToggle),
                           button_horn_(kPinInputButtonHorn_, &horn_, Button::ButtonTypes::kMomentary),
                           button_highbeam_(kPinInputButtonHighBeam_, &light_headlight_, Button::ButtonTypes::kToggle),
                           button_brake_(kPinInputButtonBrake_, &light_tail_, Button::ButtonTypes::kMomentary),
                           button_power_(kPinInputButtonPower_, &engine_, Button::ButtonTypes::kPower)
{
    display_dash_.Setup();
}

// Switches on permenant power and records start time.
// Equivalent to entering the accessory power mode in a car from off.
void Motorcycle::PowerOn(void)
{
    digitalWrite(Motorcycle::kPinOutputPower_, HIGH);
    UpdateTimeEnterAccessory();
}

// Switches off permenant power, resets components, and saves the odometer.
// Equivalent to entering the off power mode in a car.
void Motorcycle::PowerOff(void)
{
    odometer_.SaveOdometer();
    digitalWrite(Motorcycle::kPinOutputPower_, LOW);
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

unsigned int Motorcycle::GetTimeEnterAccessory(void) const
{
    return time_enter_accessory_;
}

void Motorcycle::UpdateTimeEnterAccessory(void)
{
    time_enter_accessory_ = millis();
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
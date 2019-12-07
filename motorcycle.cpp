#include "motorcycle.h"

Motorcycle::Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationPercentage, unsigned int const kEmergencyBrakeDecelerationPercentage, unsigned int const kTailLightStrobeInterval, Display &display_dash, unsigned int const kPinOutputPower) : engine_(engine), kPinInputSensorSpeed_(kPinInputSensorSpeed), kPinInputAdjustmentSpeed_(kPinInputAdjustmentSpeed), kAutoBrakeDecelerationPercentage_(kAutoBrakeDecelerationPercentage), kEmergencyBrakeDecelerationPercentage_(kEmergencyBrakeDecelerationPercentage), kTailLightStrobeInterval_(kTailLightStrobeInterval), display_dash_(display_dash), kPinOutputPower_(kPinOutputPower)
{
}

int Motorcycle::On()
{
    // Switch on permenant power.
    digitalWrite(Motorcycle::kPinOutputPower_, HIGH);
    engine_stop_time_ = millis();
}

int Motorcycle::Off()
{
    Motorcycle::engine_.Stop();
    digitalWrite(Motorcycle::kPinOutputPower_, LOW);
}

bool Motorcycle::GetSensorStandState()
{
    return false;
}

bool Motorcycle::GetSafetyState()
{
    return (GetSensorStandState());
}

unsigned int Motorcycle::GetSpeed() const
{
    return analogRead(Motorcycle::kPinInputSensorSpeed_);
    // TODO: Add adjustment settings.
}

void Motorcycle::AutoBrakeLight()
{
    // if (Motorcycle::GetSpeed() < 1 || (Motorcycle::GetSpeed() < Motorcycle::previous_speed * (1 - (Motorcycle::kAutoBrakeDecelerationPercentage_ * (Motorcycle::milliseconds_passed/1000)))) {
    //     Motorcycle::brake.SetState(HIGH);
    // } else {
    //     brake.SetState(LOW);
    // }
}

void Motorcycle::EmergencyBrakeStrobe()
{
    //   if (Motorcycle::GetSpeed < (Motorcycle::previous_speed * (1 - (Motorcycle::kEmergencyBrakeDecelerationPercentage_ * (utility::TimePassed(Motorcycle::timestamp_previous_speed)/1000))))) {
    //     if(utility::IntervalPassed(Motorcycle::brake.GetTimestampModified(), Motorcycle::kTailLightStrobeInterval_)) {
    //       Motorcycle::brake.SetState(!Motorcycle::brake.GetState());
    //     }
    //   }
}

void Motorcycle::PowerButton()
{
    Motorcycle::engine_.Start();
}
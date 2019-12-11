#include "motorcycle.h"

Motorcycle::Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationPercentage, unsigned int const kEmergencyBrakeDecelerationPercentage, unsigned int const kTailLightStrobeInterval, Display &display_dash, unsigned int const kPinOutputPower) : engine_(engine), kPinInputSensorSpeed_(kPinInputSensorSpeed), kPinInputAdjustmentSpeed_(kPinInputAdjustmentSpeed), kAutoBrakeDecelerationPercentage_(kAutoBrakeDecelerationPercentage), kEmergencyBrakeDecelerationPercentage_(kEmergencyBrakeDecelerationPercentage), kTailLightStrobeInterval_(kTailLightStrobeInterval), display_dash_(display_dash), kPinOutputPower_(kPinOutputPower)
{
}

int Motorcycle::PowerOn()
{
    // Switch on permenant power.
    digitalWrite(Motorcycle::kPinOutputPower_, HIGH);
    time_enter_acc_ = millis();
}

int Motorcycle::PowerOff()
{
    // TODO: Clear display and return speedo.
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

unsigned int Motorcycle::SpeedComparison()
{
    static unsigned int speed_last_recorded_;
    static unsigned int time_last_recorded_;

    if (utility::IntervalPassed(time_last_recorded_, 1000)) {
        return ((Motorcycle::GetSpeed() / speed_last_recorded_) * ((time_last_recorded_ - millis()) / 1000));
    }
}

void Motorcycle::AutoBrakeLight()
{
    // if (Motorcycle::GetSpeed() < 1 || Motorcycle::SpeedComparison() > kAutoBrakeDecelerationPercentage_) {
    //     Motorcycle::brake.SetState(HIGH);
    // }
}

void Motorcycle::EmergencyBrakeStrobe()
{
    // static unsigned int time_last_cycled_;

    // if (Motorcycle::GetSpeed() < 1 || Motorcycle::SpeedComparison() > kAutoBrakeDecelerationPercentage_) {
    //     if (time_last_cycled_ > kTailLightStrobeInterval_){
    //         Motorcycle::brake.SetState(!break.GetState());
    //     }
    // }
}
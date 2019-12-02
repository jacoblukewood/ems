#include "motorcycle.h"

Motorcycle::Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationPercentage, unsigned int const kEmergencyBrakeDecelerationPercentage, unsigned int const kTailLightStrobeInterval, Display &display_dash) : engine_(engine), kPinInputSensorSpeed_(kPinInputSensorSpeed), kPinInputAdjustmentSpeed_(kPinInputAdjustmentSpeed), kAutoBrakeDecelerationPercentage_(kAutoBrakeDecelerationPercentage), kEmergencyBrakeDecelerationPercentage_(kEmergencyBrakeDecelerationPercentage), kTailLightStrobeInterval_(kTailLightStrobeInterval), display_dash_(display_dash)
{
}

int Motorcycle::Start()
{

    if (engine_.Start() == EXIT_FAILURE)
    {
        // Motorcycle::display_dash_.PrintBottom("Unable to Start", Display::Alignment::kCenter);
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}

int Motorcycle::Stop()
{
    // Ensure the bike is going less than 5 km/h
    if (GetSpeed() <= 5)
    {
        return Motorcycle::engine_.Engine();
    }
    else
    {
        return EXIT_FAILURE;
    }
}

bool Motorcycle::GetRunningState()
{
    return false;
}

bool Motorcycle::GetSensorStandState()
{
    return false;
}

unsigned int Motorcycle::GetSpeed() const
{
    return analogRead(Motorcycle::kPinInputSensorSpeed_);
    // TODO: Add adjustment settings.
}

void Motorcycle::AutoBrakeLight()
{
    // if (Motorcycle::GetSpeed() < 2 || (Motorcycle::GetSpeed() < Motorcycle::previous_speed * (1 - (Motorcycle::kAutoBrakeDecelerationPercentage_ * (Motorcycle::milliseconds_passed/1000)))) {
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

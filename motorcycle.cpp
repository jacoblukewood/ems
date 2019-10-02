#include "motorcycle.h"

Motorcycle::Motorcycle(Engine &engine, unsigned int const kPinInputSensorSpeed, unsigned int const kPinInputAdjustmentSpeed, unsigned int const kAutoBrakeDecelerationPercentage, unsigned int const kEmergencyBrakeDecelerationPercentage, unsigned int const kTailLightStrobeInterval) : engine_(engine), kPinInputSensorSpeed_(kPinInputSensorSpeed), kPinInputAdjustmentSpeed_(kPinInputAdjustmentSpeed), kAutoBrakeDecelerationPercentage_(kAutoBrakeDecelerationPercentage), kEmergencyBrakeDecelerationPercentage_(kEmergencyBrakeDecelerationPercentage), kTailLightStrobeInterval_(kTailLightStrobeInterval) {
    
}

int Motorcycle::StartMotorcycle() {
    // Motorcycle::display_dash_.PrintTop("BMW", Display::Alignment::kCenter);
    // Motorcycle::display_dash_.PrintBottom("Ready to Start", Display::Alignment::kCenter);
    // Motorcycle::display_dash_.Update();

    if(engine_.StartEngine() == EXIT_FAILURE) {
        // Motorcycle::display_dash_.PrintBottom("Unable to Start", Display::Alignment::kCenter);
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

int Motorcycle::StopMotorcycle() {
    // Ensure the bike is going less than 5 km/h
    if (CurrentSpeed() <= 5) {
        return Motorcycle::engine_.StopEngine();
    } else {
        return EXIT_FAILURE;
    }
}

// bool GetRunningState() {
//     return false;
// }

// bool GetSensorStandState() {
//     return false;
// }

unsigned int Motorcycle::CurrentSpeed() const {
    return analogRead(Motorcycle::kPinInputSensorSpeed_);
    // TODO: Add adjustment settings.
}

void Motorcycle::AutoBrakeLight() {
    // if (Motorcycle::CurrentSpeed() < 2 || (Motorcycle::CurrentSpeed() < Motorcycle::previous_speed * (1 - (Motorcycle::kAutoBrakeDecelerationPercentage_ * (Motorcycle::milliseconds_passed/1000)))) {
    //     Motorcycle::brake.SetState(HIGH);
    // } else {
    //     brake.SetState(LOW);
    // }
}

 void Motorcycle::EmergencyBrakeStrobe(){
//   if (Motorcycle::CurrentSpeed < (Motorcycle::previous_speed * (1 - (Motorcycle::kEmergencyBrakeDecelerationPercentage_ * (utility::TimePassed(Motorcycle::timestamp_previous_speed)/1000))))) {
//     if(utility::IntervalPassed(Motorcycle::brake.GetTimestampModified(), Motorcycle::kTailLightStrobeInterval_)) {
//       Motorcycle::brake.SetState(!Motorcycle::brake.GetState());
//     }
//   }
 }

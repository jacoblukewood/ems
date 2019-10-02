#include "engine.h"
#include "utility.h"

Engine::Engine(unsigned int const kTimeoutCranking, unsigned int const kTachometerRunningMinimum, unsigned int const kTachometerRedline, unsigned int const kPinOutputPoints, unsigned int const kPinOutputStarterMotor, unsigned int const kPinInputSensorTachometer) : kPinOutputPoints_(kPinOutputPoints), kPinOutputStarterMotor_(kPinOutputStarterMotor), kPinInputSensorTachometer_(kPinInputSensorTachometer), kTimeoutCranking_(kTimeoutCranking), kTachometerRunningMinimum_(kTachometerRunningMinimum), kTachometerRedline_(kTachometerRedline) {

}

bool Engine::StartEngine() {
    start_attempt_time_ = millis();

    digitalWrite(Engine::kPinOutputPoints_, HIGH);
    digitalWrite(Engine::kPinOutputStarterMotor_, HIGH);

    if (EngineStatus() == HIGH) {
        // Engine has started.
        digitalWrite(Engine::kPinOutputStarterMotor_, LOW);
        return EXIT_SUCCESS;
    } else if (utility::IntervalPassed(Engine::start_attempt_time_, Engine::kTimeoutCranking_)) {
        // Craking timeout exceeded.
        digitalWrite(Engine::kPinOutputPoints_, LOW);
        digitalWrite(Engine::kPinOutputStarterMotor_, LOW);
        return EXIT_FAILURE;
    } else {
      return EXIT_FAILURE; // check this, added to remove non-void return warning
    }
}

bool Engine::StopEngine() {
    digitalWrite(Engine::kPinOutputPoints_, LOW);
    return EXIT_SUCCESS;
}

bool Engine::EngineStatus(void) const {
    return (Engine::CurrentTachometer(Engine::kPinInputSensorTachometer_) > Engine::kTachometerRunningMinimum_);  // If the current tachometer is greater than the minimum running value (RUNNING_TACHOMETER) than the bike is started.
}

// Convert the analog reading (which goes from 0 - 1023) RPM based on redline
unsigned int Engine::CurrentTachometer(const int kPinInputSensorTachometer) const {
    float tachometer_ = analogRead(kPinInputSensorTachometer) * (Engine::kTachometerRedline_ / 1023.0);
    return tachometer_;
}

#include "engine.h"
#include "utility.h"

Engine::Engine(unsigned int const kTimeoutCranking, unsigned int const kTachometerRunningMinimum, unsigned int const kTachometerRedline, unsigned int const kPinOutputPoints, unsigned int const kPinOutputStarterMotor, unsigned int const kPinInputSensorTachometer) : kPinOutputPoints_(kPinOutputPoints), kPinOutputStarterMotor_(kPinOutputStarterMotor), kPinInputSensorTachometer_(kPinInputSensorTachometer), kTimeoutCranking_(kTimeoutCranking), kTachometerRunningMinimum_(kTachometerRunningMinimum), kTachometerRedline_(kTachometerRedline)
{
}

bool Engine::Start(void) const
{
    if (!GetState())
    {
        // If engine is not running
        start_attempt_time_ = millis();

        digitalWrite(Engine::kPinOutputPoints_, HIGH);
        digitalWrite(Engine::kPinOutputStarterMotor_, HIGH);

        if (GetState())
        {
            // If engine has started.
            digitalWrite(Engine::kPinOutputStarterMotor_, LOW);
            return EXIT_SUCCESS;
        }
        else if (utility::IntervalPassed(Engine::start_attempt_time_, Engine::kTimeoutCranking_))
        {
            // Craking timeout exceeded, give up.
            digitalWrite(Engine::kPinOutputPoints_, LOW);
            digitalWrite(Engine::kPinOutputStarterMotor_, LOW);
            return EXIT_FAILURE;
        }
        else
        {
            return EXIT_FAILURE; // TODO: check this, added to remove non-void return warning
        }
    }
}

bool Engine::Stop(void) const
{
    digitalWrite(Engine::kPinOutputPoints_, LOW);
    return EXIT_SUCCESS;
}

bool Engine::GetState(void) const
{
    return (Engine::GetTachometer(Engine::kPinInputSensorTachometer_) > Engine::kTachometerRunningMinimum_); // If the current tachometer is greater than the minimum running value (RUNNING_TACHOMETER) than the bike is started.
}

// Convert the analog reading (which goes from 0 - 1023) RPM based on redline
unsigned int Engine::GetTachometer(const int kPinInputSensorTachometer) const
{
    float tachometer_ = analogRead(kPinInputSensorTachometer) * (Engine::kTachometerRedline_ / 1023.0);
    return tachometer_;
}
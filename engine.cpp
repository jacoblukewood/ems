#include "engine.h"

#include <Arduino.h>

#include "helper.h"

Engine::Engine(unsigned int const kTachometerRedline, unsigned int const kTachometerRunningMinimum, unsigned int const kTimeoutCranking, unsigned int const kPinInputSensorTachometer, unsigned int const kPinOutputPoints, unsigned int const kPinOutputStarterMotor) : kTachometerRedline(kTachometerRedline), kTachometerRunningMinimum(kTachometerRunningMinimum), kTimeoutCranking(kTimeoutCranking), kPinInputSensorTachometer(kPinInputSensorTachometer), kPinOutputPoints(kPinOutputPoints), kPinOutputStarterMotor(kPinOutputStarterMotor)
{
}

bool Engine::Start(void)
{
    if (!GetState())
    {
        // If engine is not running
        start_attempt_time_ = millis();

        digitalWrite(Engine::kPinOutputPoints, HIGH);
        digitalWrite(Engine::kPinOutputStarterMotor, HIGH);

        if (GetState())
        {
            // If engine has started.
            digitalWrite(Engine::kPinOutputStarterMotor, LOW);
            return true;
        }
        else if (helper::IntervalPassed(Engine::start_attempt_time_, Engine::kTimeoutCranking))
        {
            // Craking timeout exceeded, give up.
            digitalWrite(Engine::kPinOutputPoints, LOW);
            digitalWrite(Engine::kPinOutputStarterMotor, LOW);
            return false;
        }
        else
        {
            return false; // TODO: check this, added to remove non-void return warning
        }
    }
}

void Engine::Stop(void) const
{
    digitalWrite(Engine::kPinOutputPoints, LOW);
}

bool Engine::GetState(void) const
{
    return (Engine::GetTachometer() > Engine::kTachometerRunningMinimum); // If the current tachometer is greater than the minimum running value (RUNNING_TACHOMETER) than the bike is started.
}

// Convert the analog reading (which goes from 0 - 1023) RPM based on redline
unsigned int Engine::GetTachometer(void) const
{
    float tachometer_ = analogRead(kPinInputSensorTachometer) * (Engine::kTachometerRedline / 1023.0);
    return tachometer_;
}

bool Engine::GetRedlineState(void) const
{
    return (GetTachometer() >= kTachometerRedline);
}
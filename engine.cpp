// engine.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "engine.h"

#include <Arduino.h>

#include "utility.h"

Engine::Engine(unsigned int const tachometer_redline, unsigned int const tachometer_running_minimum_rpm, unsigned int const timeout_cranking, unsigned int const pin_input_sensor_tachometer, unsigned int const pin_output_points, unsigned int const pin_output_starter_motor)
    : kTachometerRedline(tachometer_redline)
    , kTachometerRunningMinimumRPM(tachometer_running_minimum_rpm)
    , kTimeoutCranking(timeout_cranking)
    , kPinInputSensorTachometer(pin_input_sensor_tachometer)
    , kPinOutputPoints(pin_output_points)
    , kPinOutputStarterMotor(pin_output_starter_motor)
    { }


void Engine::Start(void) {
    if (!IsRunning()) {
        // If engine is not running
        start_attempt_time_ = millis();

        digitalWrite(kPinOutputPoints, HIGH);   // TODO: Create Object
        digitalWrite(kPinOutputStarterMotor, HIGH); // TODO: Create Object

        while(!utility::IntervalPassed(start_attempt_time_, kTimeoutCranking) || !IsRunning()) {
        }

        if (IsRunning()) {
            digitalWrite(kPinOutputStarterMotor, LOW);
        } else {
            // Craking timeout exceeded, give up.
            digitalWrite(kPinOutputPoints, LOW);
            digitalWrite(kPinOutputStarterMotor, LOW);
            throw("CRANKING_TIMEOUT_EXCEEDED"); // TODO: Create exception class
        } 
    } else {
        throw("ENGINE_ALREADY_RUNNING"); // TODO: Create exception class
    }
}


void Engine::Stop(void) const {
    digitalWrite(kPinOutputPoints, LOW);
}


bool Engine::IsRunning(void) const {
    return (GetTachometer() > kTachometerRunningMinimumRPM);  // If the current tachometer is greater than the minimum running value (RUNNING_TACHOMETER) than the bike is started.
}


// Convert the analog reading (which goes from 0 - 1023) RPM based on redline
unsigned int Engine::GetTachometer(void) const {
    float tachometer_ = analogRead(kPinInputSensorTachometer) * (Engine::kTachometerRedline / 1023.0); // TODO fix magic number
    return tachometer_;
}


bool Engine::IsRedlining(void) const {
    return (GetTachometer() >= kTachometerRedline);
}

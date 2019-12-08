// ems.ino - BMW R80 electronics management system.
// Written 2019 by Jacob Wood.

#include <Arduino.h>
#include <HardwareSerial.h>
#include "motorcycle.h"
#include "engine.h"
#include "accessory.h"
#include "indicator.h"
#include "display.h"
#include "light.h"
#include "utility.h"
#include "button.h"
#include "rfid.h"

// Constants
static float const kTachometerRunningMinimum = 10.0; // * CONFIGURABLE * An RPM value which is below the lowest RPM the engine could hit when running but well above the RPM the engine could hit when the start motor is running.
static float const kAutoBrakeDecelerationPercentage = 0.04; // * CONFIGURABLE *
static float const kEmergencyBrakeDecelerationPercentage = 0.10; // * CONFIGURABLE * Speed drop/second in a decimal pecentage.
static unsigned int const kTimeoutCranking = 3500; // * CONFIGURABLE * The amount of milliseconds to run the start motor before timing out if the engine has not started.
static unsigned int const kOffHoldTime = 5000; // * CONFIGURABLE * The length of time in milliseconds the start button should be held to turn the engine off.
static unsigned int const kFlashRate = 120; // * CONFIGURABLE * Times per minute to flash indicators (Australian standards specify between 60 and 120).
static unsigned int const kTailLightBrightness = 20; // * CONFIGURABLE * A brightness value between 0 and 255 to be used for the  tail light brightness when the break light is off.
static unsigned int const kTachometerRedline = 8000; // * CONFIGURABLE *
static unsigned int const kTailLightStrobeInterval = 100; // * CONFIGURABLE * Milliseconds between on/off strobe.
static unsigned int const kKey = 123;

// Pins
// Outputs
// Buttons
static unsigned int const kPinOutputIndicatorLeft = 8;
static unsigned int const kPinOutputIndicatorRight = 9;
static unsigned int const kPinOutputPower = 10;
static unsigned int const kPinOutputHorn = 11;
static unsigned int const kPinOutputHeadlight = 12;
static unsigned int const kPinOutputHighBeam = 13;
static unsigned int const kPinOutputTailLight = A6;

// Engine
static unsigned int const kPinOutputPoints = 14;
static unsigned int const kPinOutputStarterMotor = 15;

// Display
static unsigned int const kPinOutputDisplaySDA = 20;
static unsigned int const kPinOutputDisplaySCL = 21;

// Inputs
// Buttons
static unsigned int const kPinInputButtonIndicatorLeft = 2;  // Right Indicator Button - TOGGLE
static unsigned int const kPinInputButtonIndicatorRight = 3; // Left Indicator Button - TOGGLE
static unsigned int const kPinInputButtonPower = 4;          // Start Button - MOMENTARY
static unsigned int const kPinInputButtonHorn = 5;           // Horn Button - MOMENTARY
static unsigned int const kPinInputButtonHighBeam = 6;       // High Beam Button - TOGGLE
static unsigned int const kPinInputButtonBrake = 7;          // Brake Light Button - MOMENTARY

// Sensors
static unsigned int const kPinInputSensorTachometer = A0; // Tachometer Analogue Input
static unsigned int const kPinInputSensorSpeed = A1;      // Speedometer Digital Input - Must be a valid interrupt pin (https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
static unsigned int const kPinInputSensorNeutral = A2;
static unsigned int const kPinInputSensorStand = A3;
static unsigned int const kPinInputSensorClutch = A4;

// Adjustments
static unsigned int const kPinInputAdjustmentSpeed = A5;

// Objects
// Outputs
Engine engine(kTimeoutCranking, kTachometerRunningMinimum, kTachometerRedline, kPinOutputPoints, kPinOutputStarterMotor, kPinInputSensorTachometer);
Display display_dash;
Motorcycle motorcycle(engine, kPinInputSensorSpeed, kPinInputAdjustmentSpeed, kAutoBrakeDecelerationPercentage, kEmergencyBrakeDecelerationPercentage, kTailLightStrobeInterval, display_dash, kPinOutputPower);

// Accessories
Indicator indicator_left(kPinOutputIndicatorLeft, kFlashRate, motorcycle);
Indicator indicator_right(kPinOutputIndicatorRight, kFlashRate, motorcycle);
Accessory horn(kPinOutputHorn);
Light headlight(kPinOutputHeadlight, kPinOutputHighBeam);
Light tail_light(kPinOutputTailLight, kTailLightBrightness);
Button button_indicator_left(kPinInputButtonIndicatorLeft, &indicator_left, Button::ButtonTypes::kToggle);
Button button_indicator_right(kPinInputButtonIndicatorRight, &indicator_right, Button::ButtonTypes::kToggle);
Button button_horn(kPinInputButtonHorn, &horn, Button::ButtonTypes::kMomentary);
Button button_highbeam(kPinInputButtonHighBeam, &headlight, Button::ButtonTypes::kToggle);
Button button_brake(kPinInputButtonBrake, &tail_light, Button::ButtonTypes::kMomentary);
Button button_power(kPinInputButtonPower, &motorcycle, Button::ButtonTypes::kPower);
RFID rfid(kKey);

void setup()
{
  while(!rfid.Verify()) {
    display_dash.PrintLnCenter("Invalid Key", 0);
  }

  motorcycle.On();
  display_dash.Setup();
}

void loop()
{
  if (engine.GetState())
  {
    // If engine is running.
    if (button_power.GetState() || !motorcycle.GetSafetyState()) {
      engine.Stop();
      motorcycle.engine_stop_time_ = millis();
    }
  }
  else
  {
    // If engine is not running.
    if (button_power.GetState() || motorcycle.GetSafetyState()) {
      engine.Start();
    }
  }

  // Motorcycle off after non-engine running timeout
  if (utility::IntervalPassed(motorcycle.engine_stop_time_, 10000)) {
    motorcycle.Off();
  }

  motorcycle.AutoBrakeLight();

  motorcycle.EmergencyBrakeStrobe();

  // Check and Action Buttons
  // Brake
  button_brake.RefreshState();

  // Horn
  button_horn.RefreshState();

  // Indicator Left
  button_indicator_left.RefreshState();

  // Indicator Right
  button_indicator_right.RefreshState();

  // High Beam
  button_highbeam.RefreshState();
}
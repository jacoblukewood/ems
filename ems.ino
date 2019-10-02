// ems.cc - BMW R80 electronics management system.
// Written 2019 by Jacob Wood.

#include "motorcycle.h"
#include "engine.h"
#include "accessory.h"
#include "indicator.h"
#include "taillight.h"
#include "headlight.h"
#include "utility.h"
#include "button.h"
#include <arduino.h>
#include <HardwareSerial.h>

// Constants
static          float const kTachometerRunningMinimum              = 10.0;   // * CONFIGURABLE * An RPM value which is below the lowest RPM the engine could hit when running but well above the RPM the engine could hit when the start motor is running.
static unsigned int   const kTimeoutCranking                       = 3500;   // * CONFIGURABLE * The amount of milliseconds to run the start motor before timing out if the engine has not started.
// put this somewhere or delete static unsigned int   const kOffHoldTime                           = 5000;    // * CONFIGURABLE * The length of time in milliseconds the start button should be held to turn the engine off.
static unsigned int   const kFlashRate                             = 120;    // * CONFIGURABLE * Times per minute to flash indicators (Australian standards specify between 60 and 120).
static unsigned int   const kTailLightBrightness                   = 20;     // * CONFIGURABLE * A brightness value between 0 and 255 to be used for the  tail light brightness when the break light is off.
static unsigned int   const kTachometerRedline                     = 8000;
static unsigned int   const kTailLightStrobeInterval               = 100;    // milliseconds between on/off strobe
static float          const kAutoBrakeDecelerationPercentage       = 0.04;
static float          const kEmergencyBrakeDecelerationPercentage  = 0.10;   // Speed drop/second in a decimal pecentage

// Outputs
  // Buttons
  static unsigned int const kPinOutputIndicatorLeft  = 8;
  static unsigned int const kPinOutputIndicatorRight = 9;
  static unsigned int const kPinOutputPower          = 10;
  static unsigned int const kPinOutputHorn           = 11;
  static unsigned int const kPinOutputHeadlight      = 12;
  static unsigned int const kPinOutputHighBeam       = 13;
  static unsigned int const kPinOutputTailLight      = A6;

  // Engine
  static unsigned int const kPinOutputPoints = 14;
  static unsigned int const kPinOutputStarterMotor = 15;

  // Display
  static unsigned int const kPinOutputDisplaySDA = 20;
  static unsigned int const kPinOutputDisplaySCL = 21;

// Inputs
  // Buttons
  static unsigned int const kPinInputButtonIndicatorLeft  = 2;  // Right Indicator Button - TOGGLE
  static unsigned int const kPinInputButtonIndicatorRight = 3;  // Left Indicator Button - TOGGLE
  static unsigned int const kPinInputButtonPower          = 4;  // Start Button - MOMENTARY
  static unsigned int const kPinInputButtonHorn           = 5;  // Horn Button - MOMENTARY
  static unsigned int const kPinInputButtonHighBeam       = 6;  // High Beam Button - TOGGLE
  static unsigned int const kPinInputButtonBrake          = 7;  // Brake Light Button - MOMENTARY

  // Sensors
  static unsigned int const kPinInputSensorTachometer  = A0; // Tachometer Analogue Input
  static unsigned int const kPinInputSensorSpeed       = A1; // Speedometer Digital Input - Must be a valid interrupt pin (https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
  static unsigned int const kPinInputSensorNeutral     = A2;
  static unsigned int const kPinInputSensorStand       = A3;
  static unsigned int const kPinInputSensorClutch      = A4;

  // Adjustments
  static unsigned int const kPinInputAdjustmentSpeed = A5;

// Outputs


Engine     engine         (kTimeoutCranking, kTachometerRunningMinimum, kTachometerRedline, kPinOutputPoints, kPinOutputStarterMotor, kPinInputSensorTachometer);
// Display    display_dash   (kPinOutputDisplaySDA, kPinOutputDisplaySCL);
Motorcycle motorcycle     (engine, kPinInputSensorSpeed, kPinInputAdjustmentSpeed, kAutoBrakeDecelerationPercentage, kEmergencyBrakeDecelerationPercentage, kTailLightStrobeInterval);

  // Accessories
  Indicator  indicator_left (kPinOutputIndicatorLeft,  kFlashRate, motorcycle);
  Indicator  indicator_right(kPinOutputIndicatorRight, kFlashRate, motorcycle);
  Accessory  horn           (kPinOutputHorn);
  Headlight  headlight      (kPinOutputHeadlight, kPinOutputHighBeam);
  TailLight  tail_light     (kPinOutputTailLight, kTailLightBrightness);
Button button_indicator_left(kPinInputButtonIndicatorLeft, &indicator_left, Button::ButtonTypes::kToggle);
Button button_indicator_right(kPinInputButtonIndicatorRight, &indicator_right, Button::ButtonTypes::kToggle);
Button button_horn(kPinInputButtonHorn, &horn, Button::ButtonTypes::kMomentary);
Button button_highbeam(kPinInputButtonHighBeam, &headlight, Button::ButtonTypes::kToggle);
Button button_brake(kPinInputButtonBrake, &tail_light, Button::ButtonTypes::kMomentary);
// Button button_power(kPinInputButtonPower, motorcycle, Button::ButtonTypes::kMomentary);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // if (motorcycle.GetRunningState() == HIGH) {
  //   // display_dash.PrintSpeed();
  //   // display_dash.PrintOdometer();
  //   // display_dash.Refresh();
  // } else {
  //   // Turn off points if motorcycle has failed to start, has stalled, or has been turned off.
  //   motorcycle.StopMotorcycle();
  // }
  
//motorcycle.AutoBrakeLight();

//motorcycle.EmergencyBrakeStrobe();

  // Stand Safety Shut-Off
  // if (motorcycle.GetSensorStandState() == HIGH) {
  //   motorcycle.StopMotorcycle();
  //   // add something into the start button function to allow turning the points back on without engaging starter so if the stand is put back up the engine continues running TODO
  // }

  // Check and Action Buttons
  // Brake
  button_brake.RefreshState();

//  // Horn
  button_horn.RefreshState();

  // Indicator Left
  button_indicator_left.RefreshState();

  // Indicator Right
  button_indicator_right.RefreshState();

//  // High Beam
  button_highbeam.RefreshState();
}

#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
#include <HardwareSerial.h>

#include "helper.h"
#include "accessory.h"
#include "indicator.h"

class Button
{
public:
    enum ButtonTypes
    {
        kToggle,
        kMomentary,
        kPower
    };
    Button(int kPinInput, Accessory *output, enum Button::ButtonTypes kButtonType);
    Button(int kPinInput, Motorcycle *output, enum Button::ButtonTypes kButtonType);
    void RefreshState();
    bool GetState();
    void SetState(bool state);

private:
    unsigned int const kPinInput_;
    Accessory *output_;
    Motorcycle *motorcycle_;
    ButtonTypes type_;
    unsigned long timestamp_modified_;
    bool state_;
    static unsigned int const kDebounce_ = 300; // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
};

#endif // BUTTON_H

#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
#include <HardwareSerial.h>

#include "utility.h"
#include "accessory.h"
#include "indicator.h"

class Button
{
public:
    enum ButtonTypes
    {
        kToggle,
        kMomentary
    };
    Button(int kPinInput, Accessory *output, enum Button::ButtonTypes kButtonType);
    void RefreshState();
    bool GetState();
    void SetState(bool state);

private:
    int kPinInput_;
    Accessory *output_;
    ButtonTypes type_;
    unsigned long timestamp_modified_;
    bool state_;
    static unsigned int const kDebounce_ = 300; // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
};

#endif // BUTTON_H

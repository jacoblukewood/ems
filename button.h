#ifndef EMS_BUTTON_SRC_H_
#define EMS_BUTTON_SRC_H_

#include "accessory.h"
#include "engine.h"

class Button
{
public:
    enum ButtonTypes
    {
        kToggle,
        kMomentary,
        kPower
    };
    Button(int const kPinInput, Accessory* output, enum Button::ButtonTypes const kButtonType);
    Button(int const kPinInput, Engine* engine, enum Button::ButtonTypes const kButtonType);
    void RefreshState(void);
    bool GetState(void) const;

private:
    unsigned int const kPinInput_;
    Accessory* output_;
    Engine* engine_;
    ButtonTypes type_;
    static unsigned int const kDebounce_ = 300; // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
    unsigned long timestamp_last_pressed_;
};

#endif // EMS_BUTTON_SRC_H_

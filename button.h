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

    Button(int const kPinInput, enum Button::ButtonTypes const kButtonType, Accessory* output);
    Button(int const kPinInput, enum Button::ButtonTypes const kButtonType, Engine* engine);

    bool GetState(void) const;
    void RefreshState(void);

private:
    static unsigned int const kDebounce = 300; // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
    unsigned int const kPinInput;

    Accessory* output_;
    Engine* engine_;
    ButtonTypes type_;

    unsigned long timestamp_last_pressed_;
};

#endif // EMS_BUTTON_SRC_H_

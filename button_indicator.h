// // Copyright 2020 Jacob Wood

// #ifndef BUTTONIMDICATOR_H_
// #define BUTTONIMDICATOR_H_

// #include "accessory.h"
// #include "engine.h"
// #include "button.h"

// class ButtonIndicator : public Button {
//  public:
//     enum ButtonIndicatorTypes {
//         kTwoButton,
//         kThreeButton
//     };

//     ButtonIndicator(int const kPinInput, enum ButtonIndicator::ButtonIndicatorTypes const kButtonType, const Accessory* const output);
//     ButtonIndicator(int const kPinInput, enum ButtonIndicator::ButtonIndicatorTypes const kButtonType, const Engine* const engine);

//     bool GetState(void) const;
//     void RefreshState(void);

//  private:
//     static unsigned int const kDebounce = 300;  // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
//     unsigned int const kPinInput;

//     Accessory* output_;
//     Engine* engine_;
//     ButtonIndicatorTypes type_;

//     unsigned long timestamp_last_pressed_;
// };

// #endif  // BUTTONIMDICATOR_H_

// Copyright 2020 Jacob Wood

#ifndef BUTTONIMDICATOR_H_
#define BUTTONIMDICATOR_H_

#include "accessory.h"
#include "engine.h"
#include "button.h"
#include "indicator.h"

class ButtonIndicator : public Button {
 public:
    ButtonIndicator(int const pin_input, int const debounce, Indicator* indicator_for_button, Indicator* contrasting_indicator);
    void Refresh(void);

 private:
    Indicator* indicator_;
    Indicator* contrasting_indicator_;
};

#endif  // BUTTONIMDICATOR_H_

// light.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood// Copyright 2020 Jacob Wood

#ifndef LIGHT_H_
#define LIGHT_H_

#include "accessory.h"

class Light : public Accessory {
 public:
    Light(unsigned int const kPinOutput);

    virtual void On(void);

    virtual void Off(void);

 private:
   bool state_;
};

#endif  // LIGHT_H_

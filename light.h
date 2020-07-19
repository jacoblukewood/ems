// light.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood// Copyright 2020 Jacob Wood

#ifndef LIGHT_H_
#define LIGHT_H_

#include "output.h"

class Light : public Output {
 public:
    Light(unsigned int const pin_output);

    unsigned int current_priority_;
};

#endif  // LIGHT_H_

// Copyright 2020 Jacob Wood

#ifndef ACCESSORY_H_
#define ACCESSORY_H_

class Accessory {
 public:
    Accessory(unsigned int const pin_output);

    int GetPinOutput(void) const;

    bool IsOn(void) const;
    void On(void);
    void Off(void);

 protected:
    unsigned int const kPinOutput;
};

#endif  // ACCESSORY_H_

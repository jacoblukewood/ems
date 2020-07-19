// Copyright 2020 Jacob Wood

#ifndef ACCESSORY_H_
#define ACCESSORY_H_

class Output {
 public:
    Output(unsigned int const pin_output);

    int GetPinOutput(void) const;

    bool IsOn(void) const;
    void On(void);
    void Off(void);
    unsigned int const kPinOutput;  // TODO: Make getter
    unsigned int lastChanged;
    int Output::GetPinOutput(void);

 protected:
   bool state_;
};

#endif  // ACCESSORY_H_

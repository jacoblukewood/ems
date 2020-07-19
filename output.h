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
    unsigned int timeLastChanged_ = 0;
    int Output::GetPinOutput(void);
    bool IsLocked(void);
    
    void Lock(void);
    void Unlock(void);

 protected:
   bool state_;
   bool allow_state_modification_ = false;
};

#endif  // ACCESSORY_H_

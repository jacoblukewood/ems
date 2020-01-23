// Copyright 2020 Jacob Wood

#ifndef ACCESSORY_H_
#define ACCESSORY_H_

class Accessory {
 public:
    Accessory(unsigned int const kPinOutput);

    bool GetLock(void) const;
    int GetPinOutput(void) const;
    bool GetState(void) const;
    unsigned long GetTimestampModified(void) const;
    void SetLock(bool const state);
    virtual void SetState(bool const state);
    void SetTimestampModified(unsigned long const timestamp_modified);

 private:
    unsigned int const kPinOutput;

    bool lock_;
    unsigned long timestamp_modified_;
};

#endif  // ACCESSORY_H_

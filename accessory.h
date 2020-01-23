#ifndef EMS_ACCESSORY_SRC_H_
#define EMS_ACCESSORY_SRC_H_

class Accessory
{
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

#endif // EMS_ACCESSORY_SRC_H_
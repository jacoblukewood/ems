#ifndef EMS_ACCESSORY_SRC_H_
#define EMS_ACCESSORY_SRC_H_

class Accessory
{
public:
    Accessory(unsigned int const kPinOutput);
    bool GetState(void) const;
    virtual void SetState(bool const state);
    unsigned long GetTimestampModified(void) const;
    void SetTimestampModified(unsigned long const timestamp_modified);
    int GetPinOutput(void) const;
    bool GetLock(void) const;
    void SetLock(bool const state);

private:
    unsigned int const kPinOutput_;
    bool lock_;
    unsigned long timestamp_modified_;
};

#endif // EMS_ACCESSORY_SRC_H_
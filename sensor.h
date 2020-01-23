#ifndef EMC_SENSOR_SRC_H_
#define EMC_SENSOR_SRC_H_

class Sensor
{
public:
    Sensor(int const kPinInput);
    
    bool GetState(void) const;

private:
    int const kPinInput;
};

#endif // EMC_SENSOR_SRC_H_

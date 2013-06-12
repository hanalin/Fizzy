#ifndef i_Fizzy_sensor_h
#define i_Fizzy_sensor_h

#include "Arduino.h"
#include "ifizzymicromouse.h"



enum SensorType {
    Unknown,
    WallDetector,
    EdgeDetector
};


class IFizzySensor {

    virtual bool sensorDetectedChange() = 0;

    virtual int16_t getValue() = 0;

    virtual void setFizzy(IFizzyMicroMouse* fizzy) = 0;
    virtual SensorType sensorType();
};

#endif

#ifndef i_Fizzy_sensor_h
#define i_Fizzy_sensor_h

#include "Arduino.h"
#include "ifizzymicromouse.h"



enum SensorType {
    Unknown,
    WallDetector,
    EdgeDetector,
    Encoder
};


class IFizzySensor {

public:

    virtual bool sensorDetectedChange() = 0;

    virtual int32_t getValue() = 0;

    virtual void setFizzy(IFizzyMicroMouse* fizzy) = 0;
    virtual void setControlMotor(FizzyMotor::Motor motor) = 0;
    virtual FizzyMotor::Motor controlMotor() = 0;

    virtual SensorType sensorType() = 0;

    virtual void stabilize() = 0;
};

#endif

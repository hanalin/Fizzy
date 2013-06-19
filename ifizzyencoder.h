#ifndef i_Fizzy_encoder_h
#define i_Fizzy_encoder_h

#include "Arduino.h"
#include "ifizzysensor.h"
#include "ifizzysubsystem.h"

class IFizzyEncoder : public IFizzySensor {

public:
    // use this instead of IFizzySensor::getValue()
    virtual uint32_t getCount() = 0;

    virtual int16_t getClickTravel() = 0;
    virtual void setClickTravel(int16_t mm) = 0;

    virtual void resetOdometer() = 0;
    virtual uint32_t odometerCount() = 0;
    virtual uint32_t odometer() = 0;

    virtual void onInterrupt() = 0;


#pragma region Inherited from IFizzySensor

    virtual void stabilize() = 0;
    virtual FizzyMotor::Motor controlMotor() = 0;

#pragma endregion
};


#endif

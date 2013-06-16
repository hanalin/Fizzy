#ifndef i_Fizzy_encoder_h
#define i_Fizzy_encoder_h

#include "Arduino.h"
#include "ifizzysensor.h"
#include "ifizzymicromouse.h"

class IFizzyEncoder : IFizzySensor {

public:
    // use this instead of IFizzySensor::getValue()
    virtual uint32_t getCount() = 0;

    virtual int16_t getClickTravel() = 0;
    virtual void setClickTravel(int16_t mm) = 0;

    virtual void onInterrupt() = 0;


#pragma region Inherited

    virtual void stabilize() = 0;

#pragma endregion
};


#endif

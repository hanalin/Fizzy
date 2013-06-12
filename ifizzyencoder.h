#ifndef i_Fizzy_encoder_h
#define i_Fizzy_encoder_h

#include "Arduino.h"
#include "ifizzysensor.h"
#include "ifizzymicromouse.h"

class IFizzyEncoder : IFizzySensor {

    virtual uint32_t getCount() = 0;

    virtual uint32_t getClickTravel() = 0;
    virtual void setClickTravel(uint32_t mm) = 0;
};


#endif
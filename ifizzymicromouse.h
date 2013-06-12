#ifndef i_Fizzy_micro_mouse_h
#define i_Fizzy_micro_mouse_h

#include "Arduino.h"

class IFizzyMicroMouse {

    virtual void breakLeftWheel(uint8_t force) = 0;
    virtual void breakRightWheel(uint8_t force) = 0;

    virtual void stopWheels() = 0;

    virtual void turnClockWise(uint16_t degree) = 0;
    virtual void turnCounterClockWise(uint16_t degree) = 0;

};

#endif

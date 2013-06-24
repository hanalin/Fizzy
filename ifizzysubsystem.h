#ifndef i_Fizzy_micro_mouse_h
#define i_Fizzy_micro_mouse_h

#include "Arduino.h"
#include "fizzy_motor.h"

class IFizzySubSystem {

public:

    virtual void brakeWheel(uint8_t force, FizzyMotor::Motor controlling) = 0;
    virtual void releasebrake(FizzyMotor::Motor controlling) = 0;

    virtual void stopWheels() = 0;

    virtual void turnClockWise(int16_t degree) = 0;

};

#endif

// fizzy_encoder.cpp.h

#ifndef _FIZZY_ENCODER_h
#define _FIZZY_ENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "fizzy_motor.h"
#include "ifizzysensor.h"
#include "ifizzyencoder.h"
#include "ifizzymicromouse.h"

class FizzyEncoder : IFizzyEncoder
{
 private:

     int interruptNum;

     // mili-meter per click/count
     int16_t travel_per_count;
     uint32_t count_per_interrupt;

     uint32_t count;
     uint32_t last_get_count;

     IFizzyMicroMouse* fizzy;
     FizzyMotor::Motor controllingMotor;

 public:

	FizzyEncoder(int int_num,
                 FizzyMotor::Motor controlling_motor,
                 uint32_t count_per_interrupt = 1);

#pragma region IFizzyEncoder

    uint32_t getCount();
    int16_t getClickTravel();

    void setClickTravel(int16_t mm);

    void onInterrupt();

#pragma endregion

#pragma region IFizzySensor

    bool sensorDetectedChange();
    int32_t getValue();

    void setFizzy(IFizzyMicroMouse* fizzy);
    virtual void setControlMotor(FizzyMotor::Motor motor);

    SensorType sensorType();

    void stabilize();

#pragma endregion

};


#endif


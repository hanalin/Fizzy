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
#include "ifizzysubsystem.h"

#define FIZZY_ENCODER_STABILIZER_BREAK  30
#define FIZZY_ENCODER_STABILIZER_DELAY  128


class FizzyEncoder : public IFizzyEncoder
{
 private:

     int interruptNum;

     // millimeter per click/count
     int16_t travel_per_count;
     uint32_t count_per_interrupt;

     uint32_t count;
     bool count_updated;
     uint32_t last_get_count;

     IFizzySubSystem* fizzy;
     FizzyMotor::Motor controllingMotor;

 public:

	FizzyEncoder(int int_num,
                 FizzyMotor::Motor controlling_motor,
                 uint32_t count_per_interrupt = (uint32_t)1);

#pragma region IFizzyEncoder

    uint32_t getCount();
    int16_t getClickTravel();

    void setClickTravel(int16_t mm);

    void resetOdometer();
    uint32_t odometerCount();
    uint32_t odometer();

    void onInterrupt();

#pragma endregion

#pragma region IFizzySensor

    bool sensorDetectedChange();
    int32_t getValue();

    void setFizzy(IFizzySubSystem* fizzy);
    void setControlMotor(FizzyMotor::Motor motor);
    FizzyMotor::Motor controlMotor();

    SensorType sensorType();

    // blocking function
    void stabilize();

#pragma endregion

};


#endif


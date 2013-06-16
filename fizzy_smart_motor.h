
/*
  fizzy_smart_motor.h - Fizzy motor driver.
  Created by Yui, June 2013.
  Released into the public domain.
*/

#ifndef Fizzy_smart_motor_h
#define Fizzy_smart_motor_h

#include "Arduino.h"
#include "Fizzy_motor.h"
#include "ifizzysensor.h"
#include "ifizzyencoder.h"
#include "ifizzymicromouse.h"

#define FIZZY_ENCODERS_COUNT    2


class FizzySmartMotor : public FizzyMotor, public IFizzyMicroMouse {

public:

	FizzySmartMotor(int leftmotor_pins[2], int rightmotor_pins[2]);

    bool addEncoder(IFizzyEncoder* encoder);
    void addSensor(IFizzySensor* sensor);

    void forward(int num_grids);

#pragma region Overriding FizzyMotor

    void left();
    void right();

#pragma endregion

    void positionControl();

#pragma region IFizzyMicroMouse

    void breakWheel(FizzyMotor::Motor controlling, uint8_t force);

    void stopWheels();

    void turnClockWise(uint16_t degree);
    void turnCounterClockWise(uint16_t degree);

#pragma endregion


private:

    int grids;

    IFizzyEncoder** encoders;
    uint8_t encoder_count;

    void initializeMembers();

    void checkEncoderDiff(int first_encoder_index, int second_encoder_index);

    class SensorList {

    public:

        SensorList(IFizzySensor* s) {
            sensor = s;
            next_sensor = NULL;
        }

        IFizzySensor* sensor;

        SensorList* next() {
            return next_sensor;
        }

        bool hasNext() {
            return next() != NULL;
        }

        void add(IFizzySensor* s) {

            SensorList* n;

            for (n = this; n->hasNext(); n = n->next()) {}

            n->next_sensor = new SensorList(s);
        }

        int length() {

            SensorList* n = this;
            int l;

            for (l = 0; n->hasNext(); n = n->next(), l++) {}

            return l;
        }


    private:

        SensorList* next_sensor;

    } *sensors;
};

#endif


/*
  fizzy_smart_motor.h - Fizzy motor driver.
  Created by Yui, June 2013.
  Released into the public domain.
*/

#ifndef Fizzy_smart_motor_h
#define Fizzy_smart_motor_h

#include "Arduino.h"

#include "fizzy_motor.h"
#include "ifizzysensor.h"
#include "ifizzyencoder.h"
#include "ifizzysubsystem.h"

#define FIZZY_ENCODERS_COUNT        2
#define FIZZY_ENCODER_DIFF_THRES    1



// Setting-up procedure in setup() or before loop()
//  1. Initilize: new FizzySmartMotor(left_motor_pins, right_motor_pins)
//  2. Add encoders: FizzySmartMotor::addEncoder(encoder)
//  3. Add IR/Distance sensors: FizzySmartMotor::addSensor(sensor)
//
// In loop()
//  1. Add FizzySmartMotor::positionControl()

class FizzySmartMotor : public FizzyMotor, public IFizzySubSystem {

public:

	FizzySmartMotor(int leftmotor_pins[2], int rightmotor_pins[2]);

    bool addEncoder(IFizzyEncoder* encoder);
    void addSensor(IFizzySensor* sensor);

    void positionControl();

    void forward(int num_grids);

#pragma region FizzyMotor Inherited

    void forward();

#pragma endregion

#pragma region Overriding FizzyMotor

    void left();
    void right();

#pragma endregion

#pragma region IFizzySubSystem

    void brakeWheel(uint8_t force, Motor m);
    void releasebrake(Motor m);

    void stopWheels();

    // blocking
    void turnClockWise(int16_t degree);

#pragma endregion


private:

    int grids;

    // Array of IFizzyEncoders
    IFizzyEncoder** encoders;
    uint8_t encoder_count;

    void initializeMembers();

    void stabilizerSystem();

    void encoderStabilizerSystem(int first_encoder_index, int second_encoder_index);
    void sensorsStabilizerSystem();

    uint32_t degree2Click(int16_t degree, bool one_wheel_only = false);

    void controlTurning(int16_t degree,
                        IFizzyEncoder* forward_motor_encoder,
                        IFizzyEncoder* backward_motor_encoder);

    // Simple list of IFizzySnesors
    class SensorList {

    public:

        SensorList(IFizzySensor* s) {

            sensor = s;
            next_sensor = NULL;

            sensors_count = 0;
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

            sensors_count++;
            n->next_sensor = new SensorList(s);
        }

        int length() {

            return sensors_count;
        }


    private:

        SensorList* next_sensor;
        uint16_t sensors_count;

    } *sensors;
};

#endif


/*
  fizzy_motor.h - Library for driving Fizzy motor.
  Created by Yui, May 2013.
  Released into the public domain.
*/
#ifndef Fizzy_motor_h
#define Fizzy_motor_h

#include "Arduino.h"

#define FIZZY_MOTOR_PIN_HIGH 255

#define FIZZY_SPEED_MAX 255
#define FIZZY_SPEED_MIN 0

#define FIZZY_MASK_MOTOR_LEFT	0xF3
#define FIZZY_MASK_MOTOR_RIGHT	0xFC
#define FIZZY_MASK_MOTOR		(FIZZY_MASK_MOTOR_LEFT & FIZZY_MASK_MOTOR_RIGHT)

#define FIZZY_STATE_MOTOR_FORWARD	1
#define FIZZY_STATE_MOTOR_BACKWARD	2


class FizzyMotor {

public:

    enum Motor {
        RightMotor,
        LeftMotor
    };

    FizzyMotor(int pins_a[2], int pins_b[2]);

    void calibrate(Motor m, uint8_t value);

    void stop();
    void forward();
    void left();
    void right();
    
    void setSpeed(uint8_t speed);
    
    void breakLeft(int force);
    void breakRight(int force);


protected:
    
    void breakWheel(uint8_t force, Motor m);


private:
    
    struct MotorInfo {
        int* pins;
        uint8_t calib_value;
    };

    MotorInfo motorLeft,
              motorRight;
    
    uint8_t reversed_speed;
    
    //	8765 4321
    //	---- ----
    //	       --	Right motor state 00: stopped, 01: forward, 10: backward
    //       --		Left motor state
    uint8_t fizzy_state;
    
    static uint8_t motorState(uint8_t state, Motor m);
    
    int getState(Motor m);
    
    void setPinMode(int* motor);

    void stopWheel(MotorInfo* motor);
    
    void forwardWheel(MotorInfo* motor, uint8_t break_force);
    void backwardWheel(MotorInfo* motor, uint8_t break_force);

    int pinValue(MotorInfo* motor, uint8_t break_force);
};

#endif

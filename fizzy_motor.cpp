#include "fizzy_motor.h"


FizzyMotor::FizzyMotor(int pins_left[2], int pins_right[2]) {

    motorLeft.pins = pins_left;
    motorRight.pins = pins_right;
    
    setPinMode(motorLeft.pins);
    setPinMode(motorRight.pins);
    
    // set speed to max
    setSpeed(FIZZY_SPEED_MAX);
    
    fizzy_state = 0;
}

#pragma region protected member functions

void FizzyMotor::forwardWheel(Motor m, uint8_t break_force) {

    switch(m) {
    
    case LeftMotor:
        forwardWheel(&motorLeft, break_force);
        fizzy_state = FIZZY_WHEEL_STATE(FIZZY_MASK_MOTOR_LEFT,
                                        motorState(FIZZY_STATE_MOTOR_FORWARD, LeftMotor));
        break;

    case RightMotor:
        forwardWheel(&motorRight, break_force);
        fizzy_state = FIZZY_WHEEL_STATE(FIZZY_MASK_MOTOR_RIGHT,
                                        motorState(FIZZY_STATE_MOTOR_FORWARD, RightMotor));
        break;
    }
}

void FizzyMotor::backwardWheel(Motor m, uint8_t break_force){
    switch(m) {
    
    case LeftMotor:
        backwardWheel(&motorLeft, break_force);
        fizzy_state = FIZZY_WHEEL_STATE(FIZZY_MASK_MOTOR_LEFT,
                                        motorState(FIZZY_STATE_MOTOR_FORWARD, LeftMotor));
        break;

    case RightMotor:
        backwardWheel(&motorRight, break_force);
        fizzy_state = FIZZY_WHEEL_STATE(FIZZY_MASK_MOTOR_RIGHT,
                                        motorState(FIZZY_STATE_MOTOR_FORWARD, RightMotor));
        break;
    }
}

void FizzyMotor::stopWheel(Motor m) {
    
    switch(m) {

    case LeftMotor:
        stopWheel(&motorLeft);
        fizzy_state &= FIZZY_MASK_MOTOR_LEFT;
        break;

    case RightMotor:
        stopWheel(&motorRight);
        fizzy_state &= FIZZY_MASK_MOTOR_RIGHT;
        break;
    }
}

#pragma endregion



#pragma region private member functions

void FizzyMotor::setPinMode(int* motor) {
    pinMode(motor[0], OUTPUT);
    pinMode(motor[1], OUTPUT);
}

void FizzyMotor::stopWheel(MotorInfo* motor) {

    analogWrite(motor->pins[0], FIZZY_MOTOR_PIN_HIGH);
    analogWrite(motor->pins[1], FIZZY_MOTOR_PIN_HIGH);
}

int FizzyMotor::pinValue(MotorInfo* motor, uint8_t break_force) {

    int pin_val = reversed_speed + motor->calib_value + break_force;

    return pin_val > FIZZY_MOTOR_PIN_HIGH ? FIZZY_MOTOR_PIN_HIGH : pin_val;
}

void FizzyMotor::forwardWheel(MotorInfo* motor, uint8_t break_force = 0) {


    analogWrite(motor->pins[0], pinValue(motor, break_force));
    analogWrite(motor->pins[1], FIZZY_MOTOR_PIN_HIGH);
}

void FizzyMotor::backwardWheel(MotorInfo* motor, uint8_t break_force = 0) {

    analogWrite(motor->pins[0], FIZZY_MOTOR_PIN_HIGH);
    analogWrite(motor->pins[1], pinValue(motor, break_force));
}

uint8_t FizzyMotor::motorState(uint8_t state, Motor m) {
    return state << 2 * m;
}

void FizzyMotor::breakWheel(uint8_t force, Motor m) {

    MotorInfo* motor = (LeftMotor == m) ? &motorLeft : &motorRight;

    int s = getState(m);

    if (FIZZY_STATE_MOTOR_FORWARD & s) {
        forwardWheel(motor, force);
    }
    else if (FIZZY_STATE_MOTOR_BACKWARD & s) {
        backwardWheel(motor, force);
    }
}

#pragma endregion


#pragma region public member functions


void FizzyMotor::setSpeed(uint8_t speed_max255) {
    reversed_speed = FIZZY_SPEED_MAX - speed_max255;
}

void FizzyMotor::forward() {

    forwardWheel(LeftMotor);
    forwardWheel(RightMotor);
}

void FizzyMotor::stop() {

    stopWheel(LeftMotor);
    stopWheel(RightMotor);    
}

void FizzyMotor::left() {

    backwardWheel(LeftMotor);
    forwardWheel(RightMotor);
}

void FizzyMotor::right() {

    backwardWheel(RightMotor);
    forwardWheel(LeftMotor);
}

int FizzyMotor::getState(Motor m) {

    return fizzy_state & ~FIZZY_MASK_MOTOR >> 2 * m;
}


void FizzyMotor::breakLeft(int force_max255) {
    breakWheel(force_max255, LeftMotor);
}

void FizzyMotor::breakRight(int force_max255) {
    breakWheel(force_max255, RightMotor);
}

void FizzyMotor::calibrate(Motor m, uint8_t value) {

    MotorInfo* m_other;
    MotorInfo* m_calibrating;

    if (LeftMotor == m) {
        m_other = &motorRight;
        m_calibrating = &motorLeft;
    }
    else {
        m_other = &motorLeft;
        m_calibrating = &motorRight;
    }

    int adj = m_other->calib_value - value;

    if (0 > adj) {
        m_other->calib_value = 0;
        m_calibrating->calib_value -= adj;
    }
    else {
        m_other->calib_value = adj;
    }
}

#pragma endregion

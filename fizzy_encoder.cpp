#include "fizzy_encoder.h"


FizzyEncoder::FizzyEncoder(int int_num,
                           FizzyMotor::Motor controlling_motor,
                           uint32_t count_per_interrupt) {

    interruptNum = int_num;
    controllingMotor = controllingMotor;
    this->count_per_interrupt = count_per_interrupt;

    last_get_count = 0;
    count = 0;
}

#pragma region Implementing IFizzyEncoder

uint32_t FizzyEncoder::getCount() {
    // assign last_get_count and return the value
    return last_get_count = count;
}

int16_t FizzyEncoder::getClickTravel() {
    return travel_per_count;
}

void FizzyEncoder::setClickTravel(int16_t milimeter) {
    travel_per_count = milimeter;
}

void FizzyEncoder::onInterrupt() {
    count += count_per_interrupt;
}

#pragma endregion



#pragma region Implementing IFizzySensor


bool FizzyEncoder::sensorDetectedChange() {
    return last_get_count != count;
}

// This only peeks count member variable.
// Doesn't mark for sensorDetectedChange()
int32_t FizzyEncoder::getValue() {
    return (uint32_t)count;
}

void FizzyEncoder::setFizzy(IFizzyMicroMouse* fizzy) {

    this->fizzy = fizzy;
}

SensorType FizzyEncoder::sensorType() {
    return Encoder;
}

void FizzyEncoder::setControlMotor(FizzyMotor::Motor motor) {
    controllingMotor = motor;
}

void FizzyEncoder::stabilize() {

    fizzy->breakWheel(30, controllingMotor);
    delay(128);
    fizzy->releaseBreak(controllingMotor);
}

#pragma endregion

#include "fizzy_encoder.h"


FizzyEncoder::FizzyEncoder(int int_num,
                           FizzyMotor::Motor controlling_motor,
                           uint32_t count_per_interrupt) {

    interruptNum = int_num;
    controllingMotor = controlling_motor;
    this->count_per_interrupt = count_per_interrupt;

    last_get_count = 0;
    count = 0;

    count_updated = false;
}

#pragma region Implementing IFizzyEncoder

uint32_t FizzyEncoder::getCount() {

    count_updated = false;
    return count;
}

int16_t FizzyEncoder::getClickTravel() {
    return travel_per_count;
}

void FizzyEncoder::setClickTravel(int16_t milimeter) {
    travel_per_count = milimeter;
}

void FizzyEncoder::resetOdometer() {
    last_get_count = count;
}

uint32_t FizzyEncoder::odometerCount() {
    return count - last_get_count;
}

uint32_t FizzyEncoder::odometer() {
    return odometerCount() * getClickTravel();
}

void FizzyEncoder::onInterrupt() {
    count += count_per_interrupt;
    count_updated = true;
}

#pragma endregion



#pragma region Implementing IFizzySensor


bool FizzyEncoder::sensorDetectedChange() {
    return count_updated;
}

// This only peeks count member variable.
// Doesn't mark for sensorDetectedChange()
int32_t FizzyEncoder::getValue() {
    return (uint32_t)count;
}

void FizzyEncoder::setFizzy(IFizzySubSystem* fizzy) {

    this->fizzy = fizzy;
}

SensorType FizzyEncoder::sensorType() {
    return Encoder;
}

void FizzyEncoder::setControlMotor(FizzyMotor::Motor motor) {
    controllingMotor = motor;
}

FizzyMotor::Motor FizzyEncoder::controlMotor() {
    return controllingMotor;
}

void FizzyEncoder::stabilize() {

    fizzy->breakWheel(FIZZY_ENCODER_STABILIZER_BREAK, controllingMotor);

    delay(FIZZY_ENCODER_STABILIZER_DELAY);

    fizzy->releaseBreak(controllingMotor);
}

#pragma endregion

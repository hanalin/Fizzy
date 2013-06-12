
#include "Arduino.h"
#include "fizzy_smart_motor.h"


FizzySmartMotor::FizzySmartMotor(int left_motor_pins[2],
                                 int right_motor_pins[2])
                                 : FizzyMotor(left_motor_pins, right_motor_pins), IFizzyMicroMouse() {

    initializeMembers();
}



#pragma region Public members

bool FizzySmartMotor::addEncoder(IFizzyEncoder* encoder) {

    if (FIZZY_ENCODERS_COUNT - 1 < encoder_count)
        return false;

    encoders[encoder_count] = encoder;
    encoder_count++;

    return true;
}

void FizzySmartMotor::addSensor(IFizzySensor* sensor) {

    if (NULL == sensors) {
        sensors = new SensorList(sensor);
    }
    else {
        sensors->add(sensor);
    }
}

void FizzySmartMotor::forward(int num_grids) {

}

void FizzySmartMotor::left() {
}


void FizzySmartMotor::right() {
}

void FizzySmartMotor::positionControl() {
}

#pragma endregion



#pragma region implementing IFizzyMicroMouse

void FizzySmartMotor::breakLeftWheel(uint8_t force) {
}

void FizzySmartMotor::breakRightWheel(uint8_t force) {
}

void FizzySmartMotor::stopWheels() {
}

void FizzySmartMotor::turnClockWise(uint16_t degree) {
}

void FizzySmartMotor::turnCounterClockWise(uint16_t degree) {
}

#pragma endregion



#pragma region Private members

void FizzySmartMotor::initializeMembers() {

    encoder_count = 0;
    encoders = new IFizzyEncoder*[FIZZY_ENCODERS_COUNT];

    sensors = NULL;
}

#pragma endregion


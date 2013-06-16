
#include "Arduino.h"
#include "fizzy_smart_motor.h"


// Setting-up procedure in setup() or before loop()
//  1. Initilize: new FizzySmartMotor(left_motor_pins, right_motor_pins)
//  2. Add encoders: FizzySmartMotor::addEncoder(encoder)
//  3. Add IR/Distance sensors: FizzySmartMotor::addSensor(sensor)
//
// In loop()
//  1. Add FizzySmartMotor::positionControl()

FizzySmartMotor::FizzySmartMotor(int left_motor_pins[2],
                                 int right_motor_pins[2])
                                 : FizzyMotor(left_motor_pins, right_motor_pins), IFizzyMicroMouse() {

    initializeMembers();
}



#pragma region Public members

bool FizzySmartMotor::addEncoder(IFizzyEncoder* encoder) {

    if (FIZZY_ENCODERS_COUNT < encoder_count + 1)
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

void FizzySmartMotor::checkEncoderDiff(int i1, int i2) {

    uint32_t c1 = encoders[i1]->getCount();
    uint32_t c2 = encoders[i2]->getCount();

    // abs(x) is a macro one keep the parens.
    if (FIZZY_ENCODER_DIFF_THRES < abs((c1 - c2))) {
        //encoders[c1 > c2 ? i1 : i2]->stabilize();
    }
}

void FizzySmartMotor::positionControl() {

    if (encoder_count > 1) {
        checkEncoderDiff(0, 1);
    }
}

#pragma endregion



#pragma region implementing IFizzyMicroMouse

void FizzySmartMotor::breakWheel(FizzyMotor::Motor controlling,
                                 uint8_t force_max255) {
    //  TODO: implement this function
}

void FizzySmartMotor::stopWheels() {
    //  TODO: implement this function
}

void FizzySmartMotor::turnClockWise(uint16_t degree) {
    //  TODO: implement this function
}

void FizzySmartMotor::turnCounterClockWise(uint16_t degree) {
    //  TODO: implement this function
}

#pragma endregion



#pragma region Private members

void FizzySmartMotor::initializeMembers() {

    encoder_count = 0;
    encoders = new IFizzyEncoder*[FIZZY_ENCODERS_COUNT];

    sensors = NULL;
}

#pragma endregion


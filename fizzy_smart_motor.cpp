#include "fizzy_smart_motor.h"


FizzySmartMotor::FizzySmartMotor(int left_motor_pins[2],
                                 int right_motor_pins[2])
                                 : FizzyMotor(left_motor_pins, right_motor_pins), IFizzySubSystem() {

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

void FizzySmartMotor::forward() {
    FizzyMotor::forward();
}

void FizzySmartMotor::left() {
    turnClockWise(-90);
}


void FizzySmartMotor::right() {
    turnClockWise(90);
}

void FizzySmartMotor::encoderStabilizerSystem(int i1, int i2) {

    uint32_t c1 = encoders[i1]->getCount();
    uint32_t c2 = encoders[i2]->getCount();

    // abs(x) is a macro one, keep the parens.
    if (FIZZY_ENCODER_DIFF_THRES < abs((c1 - c2))) {
        encoders[c1 > c2 ? i1 : i2]->stabilize();
    }
}

void FizzySmartMotor::sensorsStabilizerSystem() {

    IFizzySensor* sensor;

    for (SensorList* list = sensors; list->hasNext(); list = list->next()) {

        sensor = list->sensor;

        if(Encoder != sensor->sensorType() && sensor->sensorDetectedChange()) {
            sensor->stabilize();
        }
    }
}

void FizzySmartMotor::positionControl() {

    if (encoder_count > 1) {
        encoderStabilizerSystem(0, 1);
    }

    if (sensors != NULL && sensors->length() > 0) {
        sensorsStabilizerSystem();
    }
}

#pragma endregion



#pragma region implementing IFizzySubSystem

void FizzySmartMotor::breakWheel(uint8_t force, FizzyMotor::Motor m) {
    FizzyMotor::breakWheel(force, m);
}

void FizzySmartMotor::releaseBreak(FizzyMotor::Motor m) {
    FizzyMotor::breakWheel(0, m);
}

void FizzySmartMotor::stopWheels() {
    stop();
}

void FizzySmartMotor::turnClockWise(int16_t degree) {

    if (encoder_count > 1 && degree != 0) {

        IFizzyEncoder* forward_motor_controlling_encoder;
        IFizzyEncoder* backward_motor_controlling_encoder;

        if ((LeftMotor == encoders[0]->controlMotor() && degree > 0) ||
            (RightMotor == encoders[0]->controlMotor() && degree < 0)) {
            forward_motor_controlling_encoder = encoders[0];
            backward_motor_controlling_encoder = encoders[1];
        }
        else {
            forward_motor_controlling_encoder = encoders[1];
            backward_motor_controlling_encoder = encoders[0];
        }

        controlTurning(degree,
                       forward_motor_controlling_encoder,
                       backward_motor_controlling_encoder);
    }
}

#pragma endregion



#pragma region Private members

void FizzySmartMotor::initializeMembers() {

    encoder_count = 0;
    encoders = new IFizzyEncoder*[FIZZY_ENCODERS_COUNT];

    sensors = NULL;
}

uint32_t FizzySmartMotor::degree2Click(int16_t degree, bool one_wheel_only) {

    float c = ((float)abs(degree)) / 5.6;

    return (uint32_t)(one_wheel_only ? c * 2.0 : c);
}

void FizzySmartMotor::controlTurning(int16_t degree,
                                     IFizzyEncoder* forward_motor_encoder,
                                     IFizzyEncoder* backward_motor_encoder) {

    int target_count = degree2Click(degree);
    int odo_count;
    bool turning = true;

    forward_motor_encoder->resetOdometer();
    backward_motor_encoder->resetOdometer();
        
    Serial.print("Forward: ");
    Serial.println(forward_motor_encoder->controlMotor());
    Serial.print("Backward: ");
    Serial.println(backward_motor_encoder->controlMotor());

    forwardWheel(forward_motor_encoder->controlMotor());
    backwardWheel(backward_motor_encoder->controlMotor());

    Serial.print("ODO Count Begin: ");

    while (turning) {

        turning = false;

        for (int i = 0; i < 2; i++) {

            odo_count = encoders[i]->odometerCount();
            Serial.print(odo_count);
            Serial.print(" ");

            if (odo_count >= target_count) {
                if (FIZZY_STATE_MOTOR_STOP != getState(encoders[i]->controlMotor())) {
                    stopWheel(encoders[i]->controlMotor());
                }
            }
            else {
                if (odo_count + 9 > target_count) {
                    // smooth stopping
                    breakWheel(22 - (target_count - odo_count) * 2,
                                encoders[i]->controlMotor());
                }
                turning = true;
            }
        }
        Serial.print(",");
    }

    Serial.print("ODO Count End: ");
    Serial.println(encoders[0]->odometerCount());

}

#pragma endregion


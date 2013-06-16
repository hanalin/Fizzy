#include "fizzy_encoder.h"
#include "fizzy_smart_motor.h"

#define WHEEL_ENCODER_LEFT      2
#define WHEEL_ENCODER_RIGHT     3

#define COLLISION_LEFT          14
#define COLLISION_RIGHT         15

#define COLLISION_EDGE_LEFT     16
#define COLLISION_EDGE_RIGHT    17

//int motorLeftPins[2] =  { 6, 11 };
//int motorRightPins[2] = { 9, 10 };
int motorLeftPins[2] =  { 6,    9 };
int motorRightPins[2] = { 11,   10 };

int wheelEncoderPins[2] = { WHEEL_ENCODER_LEFT, WHEEL_ENCODER_RIGHT };
int collisionWallSensorPins[2] = { COLLISION_LEFT, COLLISION_RIGHT };
int collisionEdgeSensorPins[2] = { COLLISION_EDGE_LEFT, COLLISION_EDGE_RIGHT };

FizzySmartMotor motor(motorLeftPins, motorRightPins);

void setup()
{
    pinMode(13, OUTPUT);

    motor.calibrate(FizzyMotor::RightMotor, 16);

    Serial.begin(9600);
}

void loop()
{
    digitalWrite(13, HIGH);
	delay(1000);
    digitalWrite(13, LOW);

    //motor.forward();

    delay(200);
    digitalWrite(13, HIGH);


    for ( int i = 0; i < 256; i+=8) {
        motor.breakLeft(i);
        motor.breakRight(i);
        delay(100);
    }

    motor.stop();

    digitalWrite(13, LOW);
    delay(1000);

}

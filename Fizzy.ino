#include "fizzy_encoder.h"
#include "fizzy_smart_motor.h"

#define WHEEL_ENCODER_LEFT      2
#define WHEEL_ENCODER_RIGHT     3

#define COLLISION_LEFT          14
#define COLLISION_RIGHT         15

#define COLLISION_EDGE_LEFT     16
#define COLLISION_EDGE_RIGHT    17

#define INTERRUPT_LEFT_ENCODER  0
#define INTERRUPT_RIGHT_ENCODER 1

int motorLeftPins[2] =  { 6, 11 };
int motorRightPins[2] = { 9, 10 };
//int motorLeftPins[2] =  { 6,    9 };
//int motorRightPins[2] = { 11,   10 };

int wheelEncoderPins[2] = { WHEEL_ENCODER_LEFT, WHEEL_ENCODER_RIGHT };
int collisionWallSensorPins[2] = { COLLISION_LEFT, COLLISION_RIGHT };
int collisionEdgeSensorPins[2] = { COLLISION_EDGE_LEFT, COLLISION_EDGE_RIGHT };

FizzySmartMotor motor(motorLeftPins, motorRightPins);

IFizzyEncoder* encoder_left = new FizzyEncoder(INTERRUPT_LEFT_ENCODER, FizzyMotor::LeftMotor);
IFizzyEncoder* encoder_right = new FizzyEncoder(INTERRUPT_RIGHT_ENCODER, FizzyMotor::RightMotor);

void leftEncoderInterrupt() {
    encoder_left->onInterrupt();
}

void rightEncoderInterrupt() {
    encoder_right->onInterrupt();
}

void setup()
{
    pinMode(13, OUTPUT);

    motor.calibrate(FizzyMotor::RightMotor, 8);

    motor.addEncoder(encoder_left);
    motor.addEncoder(encoder_right);

    attachInterrupt(INTERRUPT_LEFT_ENCODER, leftEncoderInterrupt, CHANGE);
    attachInterrupt(INTERRUPT_RIGHT_ENCODER, rightEncoderInterrupt, CHANGE);

    Serial.begin(9600);
}

void loop()
{
    //digitalWrite(13, HIGH);
	delay(1000);
    digitalWrite(13, LOW);

    Serial.println("F");
    motor.forward();

    digitalWrite(13, HIGH);
    delay(640);

    motor.stop();
    digitalWrite(13, LOW);
    delay(640);

    Serial.println("L");
    motor.left();
    digitalWrite(13, HIGH);
    delay(640);

    motor.stop();
    digitalWrite(13, LOW);
    delay(640);

    Serial.println("R");
    motor.right();
    digitalWrite(13, HIGH);
    delay(640);



    //for ( int i = 0; i < 256; i += 8) {
    //    motor.breakLeft(i);
    //    motor.breakRight(i);
    //    delay(100);
    //}

    motor.stop();

    digitalWrite(13, LOW);
    delay(10000);

}

#include <Arduino.h>
#include <Servo.h>

#define PWM1_PIN 6
#define PWM2_PIN 9
#define PWM3_PIN 10
#define PWM4_PIN 11

Servo SERVO[4];

void initializeServo();
void setAngle(int pin, int angle);
int getAngle(int pin);

void initializeServo() {
  SERVO[0].attach(PWM1_PIN);
  SERVO[1].attach(PWM2_PIN);
  SERVO[2].attach(PWM3_PIN);
  SERVO[3].attach(PWM4_PIN);
}

void setAngle(int pin, int angle) { SERVO[pin].write(angle); }

int getAngle(int pin) { return SERVO[pin].read(); }

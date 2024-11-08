#include <Arduino.h>

#define SWITCH1_PIN 5
#define SWITCH2_PIN 4
#define SWITCH3_PIN 3

bool SWITCH[3] = {false, false, false};

void initializeSwitch();
bool readSwitch(int pin);
bool getSwitch(int pin);
void updateSwitch();

void initializeSwitch() {
  pinMode(SWITCH1_PIN, INPUT_PULLUP);
  s pinMode(SWITCH2_PIN, INPUT_PULLUP);
  pinMode(SWITCH3_PIN, INPUT_PULLUP);
}

bool readSwitch(int pin) { return digitalRead(pin); }

bool getSwitch(int pin) { return SWITCH[pin]; }

void updateSwitch() {
  SWITCH[0] = readSwitch(SWITCH1_PIN);
  SWITCH[1] = readSwitch(SWITCH2_PIN);
  SWITCH[2] = readSwitch(SWITCH3_PIN);
}

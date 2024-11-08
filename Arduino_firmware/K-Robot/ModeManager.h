#include <Arduino.h>

#define MODE1_PIN 7
#define MODE2_PIN 8
#define MODE3_PIN 12
#define MODE4_PIN A3
#define MODE5_PIN 2

enum Mode {
  RobotShooting,
  MissionCreate,
  Maze,
  BlockLow,
  BlockHigh,
  DEBUG,
  ModeError
};

void initializeMode();
bool readModeSwitch(int pin);
Mode getMode();

void initializeMode() {
  pinMode(MODE1_PIN, INPUT_PULLUP);
  pinMode(MODE2_PIN, INPUT_PULLUP);
  pinMode(MODE3_PIN, INPUT_PULLUP);
  pinMode(MODE4_PIN, INPUT_PULLUP);
  pinMode(MODE5_PIN, INPUT_PULLUP);
}

bool readModeSwitch(int pin) {
  bool state = digitalRead(pin);
  Serial.print("Mode switch ");
  Serial.print(pin);
  Serial.print(" state: ");
  Serial.println(state);
  return state;
}

Mode getMode() {
  bool mode_switch[5];
  mode_switch[0] = readModeSwitch(MODE1_PIN);
  mode_switch[1] = readModeSwitch(MODE2_PIN);
  mode_switch[2] = readModeSwitch(MODE3_PIN);
  mode_switch[3] = readModeSwitch(MODE4_PIN);
  mode_switch[4] = readModeSwitch(MODE5_PIN);

  if (mode_switch[0] && mode_switch[1] && mode_switch[2] && mode_switch[3] &&
      mode_switch[4]) {
    return DEBUG;
  }

  if (mode_switch[0])
    return RobotShooting;
  if (mode_switch[1])
    return MissionCreate;
  if (mode_switch[2])
    return Maze;
  if (mode_switch[3])
    return BlockLow;
  if (mode_switch[4])
    return BlockHigh;

  return ModeError;
}

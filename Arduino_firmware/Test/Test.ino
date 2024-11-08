#include "ADCManager.h"
#include "ModeManager.h"
#include "SerialManager.h"
#include "ServoManager.h"
#include "SwitchManager.h"

#include <Arduino.h>

Mode current_mode;

int angle = 0;

void setup()
{
  initializeSerial();
  initializeMode();
  initializeSwitch();
  initializeADC();
  initializeServo();
  current_mode = getMode();

  if (current_mode == ModeError) {
    sendPacket("MODE_ERROR");
    return;
  } else if (current_mode == DEBUG) {
    sendPacket("DEBUG");
  } else if (current_mode == RobotShooting) {
    sendPacket("ROBOT_SHOOTING");
  } else if (current_mode == MissionCreate) {
    sendPacket("MISSION_CREATE");
  } else if (current_mode == Maze) {
    sendPacket("MAZE");
  } else if (current_mode == BlockLow) {
    sendPacket("BLOCK_LOW");
  } else if (current_mode == BlockHigh) {
    sendPacket("BLOCK_HIGH");
  }

  for (int i = 0; i < 4; i++) {
    setAngle(i, 0);
  }
}

void loop()
{
  setAngle(0, angle);
  angle++;
  updateADC();
  updateSwitch();
  delay(500);
}

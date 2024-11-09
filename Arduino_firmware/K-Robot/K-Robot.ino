#include "ADCManager.h"
#include "ModeManager.h"
#include "SerialManager.h"
#include "ServoManager.h"
#include "SwitchManager.h"

#include <Arduino.h>

Mode current_mode;

bool timerOn = false;

void setup() {
  initializeSerial();
  initializeMode();
  initializeSwitch();
  initializeADC();
  initializeServo();
  current_mode = getMode();
  delay(100);

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
  delay(100);
}

void loop() {
  updateADC();
  updateSwitch();

  // 기본 PSD Timer Start/Stop
  if (PSD_DETECTED[0] && !timerOn) {
    sendPacket("START");
    timerOn = true;
  }
  if (PSD_DETECTED[2] && timerOn) {
    sendPacket("END");
    timerOn = false;
  }

  // 모드별 설정
  if (current_mode == BlockHigh) {
    // 차단바
    if (PSD_DETECTED[1] && timerOn) {
      delay(ADC_v[3]); // 랜덤시간 delay
      setAngle(0, -90);
    }
  } else if (current_mode == RobotShooting) {

  } else if (current_mode == MissionCreate) {
  }

  String commandRead = readPacket();
  if (commandRead == "RESET") {
    timerOn = false;
    current_mode = getMode();
    delay(100);

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
    delay(100);
  } else if (commandRead == "SERVO") {
    for (int i = 0; i < 4; i++) {
      setAngle(i, 0);
    }
    delay(100);
  }

  delay(1);
}

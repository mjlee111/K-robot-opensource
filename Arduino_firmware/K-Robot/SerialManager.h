#include <Arduino.h>

bool initializeSerial();
String generatePacket(String command);
void sendPacket(String command);
String readPacket();

bool initializeSerial() {
  Serial.begin(115200);
  while (!Serial) {
  }
  sendPacket("INIT");
  sendPacket("INIT");
  sendPacket("INIT");
  sendPacket("INIT");

  return true;
}

String generatePacket(String command) {
  String packet;
  packet += "##";
  packet += command;
  packet += "FF";
  return packet;
}

void sendPacket(String command) {
  String packet;
  packet = generatePacket(command);
  Serial.println(packet);
}

String readPacket() {
  String packet = "";
  while (Serial.available() > 0) {
    char ch = Serial.read();
    packet += ch;

    if (packet.startsWith("##") && packet.endsWith("FF")) {
      return packet;
    }

    if (packet.length() > 64) {
      packet = "";
    }
  }
  return "";
}

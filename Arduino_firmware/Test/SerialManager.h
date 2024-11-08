#include <Arduino.h>

bool initializeSerial()
{
  Serial.begin(115200);
  while (!Serial) {
  }
  return true;
}

String generatePacket(String command)
{
  String packet;
  packet += "##";
  packet += command;
  packet += "FF";
  return packet;
}

void sendPacket(String command)
{
  String packet;
  packet = generatePacket(command);
  Serial.println(packet);
}

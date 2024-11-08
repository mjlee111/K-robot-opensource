#include <Arduino.h>

bool initializeSerial();
String generatePacket(String command);
void sendPacket(String command);

bool initializeSerial()
{
  Serial.begin(115200);
  while (!Serial) {
  }
  sendPacket("INIT");
  sendPacket("INIT");
  sendPacket("INIT");
  sendPacket("INIT");

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

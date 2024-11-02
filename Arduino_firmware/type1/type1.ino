#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  writeTimerStartPacket();
  delay(1000);
  
  String data2 = generatePacket("END");
  Serial.println(data2.c_str());
  delay(1000);
}

String generatePacket(String command)
{
  String packet;
  packet += "##";
  packet += command;
  packet += "FF";
  return packet;
}

void writeTimerStartPacket()
{
  String packet = generatePacket("TIMERSTART");
  Serial.println(packet.c_str());
  delay(1);
}

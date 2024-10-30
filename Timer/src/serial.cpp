#include "../include/serial.hpp"

Serial::Serial() : serial(new QSerialPort())
{
}

Serial::~Serial()
{
  if (serial->isOpen()) {
    serial->close();
  }
  delete serial;
}

QStringList Serial::getPortNames()
{
  QStringList devicesList;

  const auto availablePorts = QSerialPortInfo::availablePorts();
  for (const QSerialPortInfo & portInfo : availablePorts) {
    QString portName = portInfo.portName();
#ifdef __linux__
    // Linux: Filter only ttyACM and ttyUSB devices
    if (portName.startsWith("ttyACM") || portName.startsWith("ttyUSB")) {
      devicesList.append(portName);
    }
#elif _WIN32
    // Windows: Filter COM ports
    if (portName.startsWith("COM")) {
      devicesList.append(portName);
    }
#endif
  }

  return devicesList;
}

bool Serial::openPort(const QString & portName, const int & baudRate)
{
  if (serial->isOpen()) {
    serial->close();
  }

  serial->setPortName(portName);
  serial->setBaudRate(baudRate);
  serial->setDataBits(QSerialPort::Data8);
  serial->setParity(QSerialPort::NoParity);
  serial->setStopBits(QSerialPort::OneStop);
  serial->setFlowControl(QSerialPort::NoFlowControl);

  return serial->open(QIODevice::ReadWrite);
}

void Serial::closePort()
{
  if (serial->isOpen()) {
    serial->close();
  }
}

void Serial::readDevice()
{
}

void Serial::writeDevice(const QByteArray & data)
{
}
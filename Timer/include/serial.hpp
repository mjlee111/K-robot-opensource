#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <QtSerialPort/QSerialPortInfo>

#include <QSerialPort>
#include <QThread>
#include <QTimer>
#include <iostream>
#include <vector>

class Serial : public QObject
{
  Q_OBJECT

public:
  explicit Serial();
  ~Serial();

  QStringList getPortNames();
  bool openPort(const QString & portName, const int & baudRate);
  void closePort();

  QSerialPort * serial;
  std::vector<QByteArray> buffer;

Q_SIGNALS:
  void dataReceived();

public slots:
  void readDevice();
  void writeDevice(const QByteArray & data);

private:
  QString portName;
  int baudRate;
};

#endif

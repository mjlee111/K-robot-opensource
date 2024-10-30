#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../include/serial.hpp"

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <iostream>

#define SERIAL_BAUDRATE 115200

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget * parent = nullptr);
  ~MainWindow();

private slots:
  void on_deviceList_currentIndexChanged(int index);
  void on_connectBtn_clicked();

private:
  Ui::MainWindow * ui;
  Serial * serial;
  QTimer * msTimer;

  void initializeSerial();

  int msec = 0;
  int sec = 0;
  int min = 0;

  QString device_name;
  bool isOpen = false;
};
#endif  // MAINWINDOW_H

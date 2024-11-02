#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../include/serial.hpp"

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
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

  enum TimerType { timer, stopwatch };

public Q_SLOTS:
  void on_deviceList_currentIndexChanged(int index);
  void on_connectBtn_clicked();
  void on_deviceResetBtn_clicked();
  void on_servoInitBtn_clicked();
  void on_timerSetBtn_clicked();
  void on_stopwatchBtn_clicked();
  void on_startBtn_clicked();
  void timerUpdate();
  void on_resetBtn_clicked();
  void on_searchBtn_clicked();

  void handleDataReceived();

private:
  Ui::MainWindow * ui;
  Serial * serial;
  QTimer * msTimer;

  void initializeSerial();
  void timerSetDialog(int & msec, int & sec, int & min);

  TimerType timerType;
  bool onCount = false;
  int msec = 0;
  int sec = 0;
  int min = 0;

  int last_msec = 0;
  int last_sec = 0;
  int last_min = 0;

  QString device_name;
  bool isOpen = false;
};
#endif  // MAINWINDOW_H

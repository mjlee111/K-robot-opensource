#include "./ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
: QMainWindow(parent), ui(new Ui::MainWindow), serial(new Serial), msTimer(new QTimer)
{
  ui->setupUi(this);
  QIcon icon(":/image/images/icon.png");
  setWindowIcon(icon);

  initializeSerial();
}

MainWindow::~MainWindow()
{
  delete serial;
  delete ui;
}

//////////////////// Functions ////////////////////

void MainWindow::initializeSerial()
{
  QStringList portNames = serial->getPortNames();
  ui->deviceList->addItems(portNames);
}

//////////////////// Slots ////////////////////

void MainWindow::on_deviceList_currentIndexChanged(int index)
{
  device_name = ui->deviceList->currentText();
}

void MainWindow::on_connectBtn_clicked()
{
  if (isOpen) {
    disconnect(serial->serial, &QSerialPort::readyRead, serial, &Serial::readDevice);

    ui->deviceList->setEnabled(true);
    ui->connectBtn->setText("Connect");
    ui->connectBtn->setStyleSheet("color: rgb(255, 0, 0);");

    isOpen = false;

    initializeSerial();
  } else if (!isOpen) {
    bool status = serial->openPort(device_name, SERIAL_BAUDRATE);

    if (status) {
      ui->deviceList->setEnabled(false);
      ui->connectBtn->setText("Disconnect");
      ui->connectBtn->setStyleSheet("color: rgb(0, 255, 0);");

      isOpen = true;

      connect(serial->serial, &QSerialPort::readyRead, serial, &Serial::readDevice);
    } else {
      QMessageBox::critical(
        nullptr, "Device Status", "Failed to open device: " + serial->serial->errorString());
      ui->deviceList->setEnabled(true);
      ui->connectBtn->setText("Connect");
      ui->connectBtn->setStyleSheet("color: rgb(255, 0, 0);");

      isOpen = false;
      initializeSerial();
    }
  }
}

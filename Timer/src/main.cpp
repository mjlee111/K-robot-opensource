#include "mainwindow.h"

#include <QApplication>
#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QRect>
#include <QScreen>
#include <QVBoxLayout>

int main(int argc, char * argv[])
{
  QApplication a(argc, argv);

  QDialog screenSelectDialog;
  screenSelectDialog.setWindowTitle("디스플레이 설정");

  QVBoxLayout * layout = new QVBoxLayout(&screenSelectDialog);

  QLabel * screenLabel = new QLabel("디스플레이 선택:");
  QComboBox * screenCombo = new QComboBox();

  QLabel * sizeLabel = new QLabel("화면 크기:");
  QComboBox * sizeCombo = new QComboBox();
  sizeCombo->addItem("전체 화면", 100);
  sizeCombo->addItem("80%", 80);
  sizeCombo->addItem("60%", 60);
  sizeCombo->addItem("40%", 40);
  sizeCombo->setCurrentIndex(1);
  QPushButton * okButton = new QPushButton("확인");

  QList<QScreen *> screens = QGuiApplication::screens();
  int selectedScreen = 0;

  for (int i = 0; i < screens.size(); i++) {
    QScreen * screen = screens[i];
    QString screenInfo = QString("Display %1 (%2x%3)")
                           .arg(i + 1)
                           .arg(screen->geometry().width())
                           .arg(screen->geometry().height());
    screenCombo->addItem(screenInfo, i);
  }

  layout->addWidget(screenLabel);
  layout->addWidget(screenCombo);
  layout->addWidget(sizeLabel);
  layout->addWidget(sizeCombo);
  layout->addWidget(okButton);

  QObject::connect(okButton, &QPushButton::clicked, &screenSelectDialog, &QDialog::accept);

  int screenSize = 80;
  if (screenSelectDialog.exec() == QDialog::Accepted) {
    selectedScreen = screenCombo->currentData().toInt();
    screenSize = sizeCombo->currentData().toInt();
  }

  QScreen * selectedDisplay = screens[selectedScreen];
  QRect screenGeometry = selectedDisplay->geometry();

  MainWindow w;
  int width = screenGeometry.width() * screenSize / 100;
  int height = screenGeometry.height() * screenSize / 100;

  w.setFixedSize(width, height);
  w.show();

  return a.exec();
}
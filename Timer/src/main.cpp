#include "mainwindow.h"

#include <QApplication>
#include <QComboBox>
#include <QDialog>
#include <QList>
#include <QPushButton>
#include <QRect>
#include <QScreen>
#include <QVBoxLayout>

int main(int argc, char * argv[])
{
  QApplication a(argc, argv);

  QDialog screenSelectDialog;
  screenSelectDialog.setWindowTitle("Select Display");

  QVBoxLayout * layout = new QVBoxLayout(&screenSelectDialog);
  QComboBox * screenCombo = new QComboBox();
  QPushButton * okButton = new QPushButton("OK");

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

  layout->addWidget(screenCombo);
  layout->addWidget(okButton);

  QObject::connect(okButton, &QPushButton::clicked, &screenSelectDialog, &QDialog::accept);

  if (screenSelectDialog.exec() == QDialog::Accepted) {
    selectedScreen = screenCombo->currentData().toInt();
  }

  QScreen * selectedDisplay = screens[selectedScreen];
  QRect screenGeometry = selectedDisplay->geometry();

  MainWindow w;
  int width = screenGeometry.width() * 0.8;
  int height = screenGeometry.height() * 0.8;

  w.setFixedSize(width, height);
  w.show();

  return a.exec();
}
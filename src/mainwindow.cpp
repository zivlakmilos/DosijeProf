#include "mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    QCoreApplication::setApplicationName("Dosije");
    QCoreApplication::setOrganizationName("Milos Zivlak");
    QCoreApplication::setOrganizationDomain("zivlak.ddns.net");

    setWindowTitle(QCoreApplication::applicationName());
}

MainWindow::~MainWindow(void)
{
}

#include "mainwindow.h"

#include <QtGui>

#include "centralwidget.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    QCoreApplication::setApplicationName("Dosije");
    QCoreApplication::setOrganizationName("Milos Zivlak");
    QCoreApplication::setOrganizationDomain("zivlak.ddns.net");

    setWindowTitle(QCoreApplication::applicationName());

    m_centralWidget = new CentralWidget(this);
    setCentralWidget(m_centralWidget);

    setupActions();
    setupMenu();
    setupToolbar();
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::setupActions(void)
{
    m_actionNoviFajl = new QAction(tr("&Novi fajl"), this);
    m_actionNoviFajl->setIcon(QIcon(tr(":img/filenew.png")));
    m_actionNoviFajl->setShortcut(tr("Ctrl+N"));

    m_actionObrisiFajl = new QAction(tr("&Obrisi fajl"), this);
    m_actionObrisiFajl->setIcon(QIcon(tr(":img/edittrash.png")));
    m_actionObrisiFajl->setShortcut(tr("Delete"));

    m_actionIzlaz = new QAction(tr("&Izlaz"), this);
    m_actionIzlaz->setIcon(QIcon(tr(":img/fileclose.png")));
    m_actionIzlaz->setShortcut(tr("Ctrl+Q"));
    connect(m_actionIzlaz, SIGNAL(triggered(bool)),
            qApp, SLOT(quit()));
}

void MainWindow::setupMenu(void)
{
    QMenu *menuPodaci = menuBar()->addMenu(tr("&Podaci"));
    menuPodaci->addAction(m_actionNoviFajl);
    menuPodaci->addAction(m_actionObrisiFajl);

    menuBar()->addAction(m_actionIzlaz);
}

void MainWindow::setupToolbar(void)
{
    QToolBar *tbPodaci = new QToolBar(tr("Podaci"), this);
    tbPodaci->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);

    tbPodaci->addAction(m_actionNoviFajl);
    tbPodaci->addAction(m_actionObrisiFajl);
    tbPodaci->addSeparator();
    tbPodaci->addAction(m_actionIzlaz);

    addToolBar(Qt::TopToolBarArea, tbPodaci);
}

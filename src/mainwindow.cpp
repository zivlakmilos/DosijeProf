#include "mainwindow.h"

#include <QtGui>
#include <QtSql>

#include "centralwidget.h"
#include "dpodaci.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    QCoreApplication::setApplicationName("Dosije");
    QCoreApplication::setOrganizationName("Milos Zivlak");
    QCoreApplication::setOrganizationDomain("zivlak.ddns.net");

    QSettings settings;
    settings.setValue("url/img", "http://zivlak.ddns.net/dosije/img/");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(QCoreApplication::organizationDomain());
    db.setDatabaseName("dosijeprof");
    db.setUserName("dosijeprof");
    db.setPassword("D0SiJePr0f1317mz");
    if(!db.open())
        qDebug() << db.lastError();

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
    connect(m_actionNoviFajl, SIGNAL(triggered(bool)),
            this, SLOT(noviFajlOnClick()));

    m_actionObrisiFajl = new QAction(tr("&Obrisi fajl"), this);
    m_actionObrisiFajl->setIcon(QIcon(tr(":img/edittrash.png")));
    m_actionObrisiFajl->setShortcut(tr("Delete"));
    connect(m_actionObrisiFajl, SIGNAL(triggered(bool)),
            this, SLOT(obrisiFajlOnClick()));

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

void MainWindow::noviFajlOnClick(void)
{
    DPodaci *dlgNoviFajl = new DPodaci(this);
    dlgNoviFajl->setWindowTitle(tr("Novi fajl"));
    if(dlgNoviFajl->exec() == QDialog::Accepted)
    {
        m_centralWidget->ucitajPodatke();
    }
}

void MainWindow::obrisiFajlOnClick(void)
{
}

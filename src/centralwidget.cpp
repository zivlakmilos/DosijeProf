#include "centralwidget.h"

#include <QtGui>

CentralWidget::CentralWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    setupGUI();
}

CentralWidget::~CentralWidget(void)
{
}

void CentralWidget::setupGUI(void)
{
    /*
     * Kreiraj vizualne komponente
     */

    m_tblPodaci = new QTableView(this);

    /*
     * Rasporedi komponente po formi
     */

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addWidget(m_tblPodaci);

    setLayout(layoutMain);
}

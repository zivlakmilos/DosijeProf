#include "centralwidget.h"

#include <QtGui>
#include <QtSql>

#include "dpodaci.h"

CentralWidget::CentralWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    m_modelPodaci = new QSqlQueryModel(this);
    ucitajPodatke();
    setupGUI();
}

CentralWidget::~CentralWidget(void)
{
}

void CentralWidget::ucitajPodatke(void)
{
    m_modelPodaci->setQuery("SELECT id, ime, prezime, jmbg FROM podaci;");
    m_modelPodaci->setHeaderData(0, Qt::Horizontal, tr("ID"));
    m_modelPodaci->setHeaderData(1, Qt::Horizontal, tr("Ime"));
    m_modelPodaci->setHeaderData(2, Qt::Horizontal, tr("Prezime"));
    m_modelPodaci->setHeaderData(3, Qt::Horizontal, tr("JMBG"));
}

void CentralWidget::setupGUI(void)
{
    /*
     * Kreiraj vizualne komponente
     */

    m_tblPodaci = new QTableView(this);
    m_tblPodaci->setModel(m_modelPodaci);
    m_tblPodaci->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tblPodaci->setColumnHidden(0, false);
    m_tblPodaci->setColumnWidth(0, 50);
    m_tblPodaci->setColumnWidth(1, 200);
    m_tblPodaci->setColumnWidth(2, 200);
    m_tblPodaci->setColumnWidth(3, 150);

    connect(m_tblPodaci, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(podaciOnDoubleClick(QModelIndex)));

    /*
     * Rasporedi komponente po formi
     */

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addWidget(m_tblPodaci);

    setLayout(layoutMain);
}

void CentralWidget::obrisiSelektovanRed(void)
{
    if(QMessageBox::warning(this, tr("Potvrda brisanja"),
                            tr("Da li ste sigurni da zelite obrisati selektovane podatke"),
                            QMessageBox::Yes | QMessageBox::No)
        != QMessageBox::Yes)
    {
        return;
    }

    QModelIndexList selekcije = m_tblPodaci->selectionModel()->selectedRows();

    for(QModelIndex selekcija : selekcije)
    {
        QModelIndex index = m_modelPodaci->index(selekcija.row(), 0);

        int id = m_modelPodaci->data(index).toInt();

        QSqlQuery query(QSqlDatabase::database());
        query.prepare("DELETE FROM podaci WHERE id=:id;");
        query.bindValue(":id", id);
        if(!query.exec())
        {
            QMessageBox::critical(this, tr("Greska prilikom brisanja podataka"),
                                  tr("Nije moguce obrisati podatke iz baze podataka"),
                                  QMessageBox::Ok);
        }
    }

    ucitajPodatke();
}

void CentralWidget::podaciOnDoubleClick(const QModelIndex &index)
{
    QModelIndex idIndex = m_modelPodaci->index(index.row(), 0);

    DPodaci *dlgPodaci = new DPodaci(this);
    dlgPodaci->setId(m_modelPodaci->data(idIndex).toInt());
    if(dlgPodaci->exec() == QDialog::Accepted)
    {
        ucitajPodatke();
    }
}

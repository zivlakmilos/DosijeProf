#include "dpodaci.h"

#include <QtGui>
#include <QtSql>

DPodaci::DPodaci(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f),
      m_id(-1)
{
    setupUi(this);
    setupGUI();
}

DPodaci::~DPodaci(void)
{
}

void DPodaci::setupGUI(void)
{
    lblSlika->setScaledContents(true);
    lblSlika->setMaximumSize(QSize(200, 200));

    buttonBox->button(QDialogButtonBox::Save)->setText(tr("Snimi"));
    buttonBox->button(QDialogButtonBox::Discard)->setText(tr("Otkazi"));

    connect(txtIme, SIGNAL(textChanged(QString)),
            this, SLOT(promenaNatpisa()));
    connect(txtPrezime, SIGNAL(textChanged(QString)),
            this, SLOT(promenaNatpisa()));
}

void DPodaci::setId(int id)
{
    m_id = id;

    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT ime,"
                  "       prezime,"
                  "       pol,"
                  "       jmbg,"
                  "       datum_rodjenja,"
                  "       adresa,"
                  "       nacionalnost,"
                  "       bracno_stanje,"
                  "       slika,"
                  "       ostali_podaci,"
                  "       misljenje "
                  "FROM podaci WHERE id=:id;");
    query.bindValue(":id", id);
    query.exec();

    if(query.next())
    {
        txtIme->setText(query.value(0).toString());
        txtPrezime->setText(query.value(1).toString());
        txtJmbg->setText(query.value(3).toString());
        deDatumRodjenja->setDate(query.value(4).toDate());
        txtAdresa->setText(query.value(5).toString());
        txtOstaliPodaci->setText(query.value(8).toString());
        txtMisljenje->setText(query.value(9).toString());
    }
}

void DPodaci::promenaNatpisa(void)
{
    setWindowTitle(tr("%1 %2").arg(txtIme->text(), txtPrezime->text()));
}

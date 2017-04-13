#include "dpodaci.h"

#include <QtGui>
#include <QtSql>
#include <QtNetwork/QtNetwork>

#include "clickablelabel.h"

DPodaci::DPodaci(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f),
      m_id(-1)
{
    setupUi(this);
    setupGUI();

    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(networkManagerFinished(QNetworkReply*)));

    connect(this, SIGNAL(accepted()),
            this, SLOT(snimi()));
}

DPodaci::~DPodaci(void)
{
}

void DPodaci::setupGUI(void)
{
    lblSlika->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lblSlika = new ClickableLabel(lblSlika);
    m_lblSlika->setScaledContents(true);
    m_lblSlika->setMaximumSize(QSize(200, 200));
    m_lblSlika->setPixmap(QPixmap(tr(":img/avatar.png")));
    connect(m_lblSlika, SIGNAL(clicked()),
            this, SLOT(lblSlikaOnClick()));


    buttonBox->button(QDialogButtonBox::Save)->setText(tr("Snimi"));
    buttonBox->button(QDialogButtonBox::Discard)->setText(tr("Otkazi"));

    cbPol->addItem(tr("M"));
    cbPol->addItem(tr("Z"));

    QStringList nacionalnost;
    nacionalnost << ""
                 << tr("Srbin")
                 << tr("Hrvat")
                 << tr("Bosnjak");
    cbNacionalnost->addItems(nacionalnost);

    QStringList bracnoStanje;
    bracnoStanje << ""
                 << tr("Slobodan/Slobodna")
                 << tr("Veren/Verena")
                 << tr("Ozenjen/Udata");
    cbBracnoStanje->addItems(bracnoStanje);

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
        txtOstaliPodaci->setText(query.value(9).toString());
        txtMisljenje->setText(query.value(10).toString());

        int polIndex = cbPol->findText(query.value(2).toString());
        if(polIndex > 0)
            cbPol->setCurrentIndex(polIndex);

        int nacionalnostIndex = cbNacionalnost->findText(query.value(6).toString());
        if(nacionalnostIndex >= 0)
        {
            cbNacionalnost->setCurrentIndex(nacionalnostIndex);
        } else
        {
            cbNacionalnost->addItem(query.value(6).toString());
            cbNacionalnost->setCurrentIndex(cbNacionalnost->count() - 1);
        }

        int bracnoStanjeIndex = cbBracnoStanje->findText(query.value(7).toString());
        if(bracnoStanjeIndex >= 0)
        {
            cbBracnoStanje->setCurrentIndex(bracnoStanjeIndex);
        } else
        {
            cbBracnoStanje->addItem(query.value(7).toString());
            cbBracnoStanje->setCurrentIndex(cbNacionalnost->count() - 1);
        }

        QSettings settings;
        QUrl url(settings.value("url/img").toString() + query.value(8).toString());
        QNetworkRequest request(url);
        m_networkManager->get(request);
    }
}

void DPodaci::promenaNatpisa(void)
{
    setWindowTitle(tr("%1 %2").arg(txtIme->text(), txtPrezime->text()));
}

void DPodaci::networkManagerFinished(QNetworkReply *reply)
{
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
        return;

    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    m_lblSlika->setPixmap(pixmap);
}

void DPodaci::lblSlikaOnClick(void)
{
    QDialog *dlgSlika = new QDialog;
    dlgSlika->setWindowTitle(txtIme->text() + " " + txtPrezime->text());

    QLabel *slika = new QLabel(dlgSlika);
    slika->setPixmap(*m_lblSlika->pixmap());

    dlgSlika->resize(slika->sizeHint());
    dlgSlika->exec();

    delete dlgSlika;
}

void DPodaci::snimi(void)
{
    QString strQuery;

    if(m_id < 0)
        strQuery = "INSERT INTO podaci(ime,"
                    "                  prezime,"
                    "                  pol,"
                    "                  jmbg,"
                    "                  datum_rodjenja,"
                    "                  adresa,"
                    "                  nacionalnost,"
                    "                  bracno_stanje,"
                    "                  ostali_podaci,"
                    "                  misljenje)"
                   "VALUES(:ime,"
                   "       :prezime,"
                   "       :pol,"
                   "       :jmbg,"
                   "       :datum_rodjenja,"
                   "       :adresa,"
                   "       :nacionalnost,"
                   "       :bracno_stanje,"
                   "       :ostali_podaci,"
                   "       :misljenje);";
    else
        strQuery = "UPDATE podaci SET"
                    "   ime=:ime,"
                    "   prezime=:prezime,"
                    "   pol=:pol,"
                    "   jmbg=:jmbg,"
                    "   datum_rodjenja=:datum_rodjenja,"
                    "   adresa=:adresa,"
                    "   nacionalnost=:nacionalnost,"
                    "   bracno_stanje=:bradno_stanje,"
                    "   ostali_podaci=:ostali_podaci,"
                    "   misljenje=:misljenje "
                   "WHERE id=:id;";

    QSqlQuery query(QSqlDatabase::database());
    query.prepare(strQuery);
    query.bindValue(":ime", txtIme->text());
    query.bindValue(":prezime", txtPrezime->text());
    query.bindValue(":pol", cbPol->currentText());
    query.bindValue(":jmbg", txtJmbg->text());
    query.bindValue(":datum_rodjenja", deDatumRodjenja->date());
    query.bindValue(":adresa", txtAdresa->text());
    query.bindValue(":nacionalnost", cbNacionalnost->currentText());
    query.bindValue(":bracno_stanje", cbBracnoStanje->currentText());
    query.bindValue(":ostali_podaci", txtOstaliPodaci->document()->toPlainText());
    query.bindValue(":misljenje", txtMisljenje->document()->toPlainText());
    if(m_id >= 0)
        query.bindValue(":id", m_id);
    query.exec();
}

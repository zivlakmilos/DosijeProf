#include "dpodaci.h"

DPodaci::DPodaci(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setupUi(this);
    setupGUI();

    lblSlika->setScaledContents(true);
    lblSlika->setMaximumSize(QSize(200, 200));
}

DPodaci::~DPodaci(void)
{
}

void DPodaci::setupGUI(void)
{
    connect(txtIme, SIGNAL(textChanged(QString)),
            this, SLOT(promenaNatpisa()));
    connect(txtPrezime, SIGNAL(textChanged(QString)),
            this, SLOT(promenaNatpisa()));
}

void DPodaci::promenaNatpisa(void)
{
    setWindowTitle(tr("%1 %2").arg(txtIme->text(), txtPrezime->text()));
}

#ifndef _W_PODACI_H_
#define _W_PODACI_H_

#include <QDialog>

#include "ui_podaci.h"
#include "clickablelabel.h"

class QNetworkAccessManager;
class QNetworkReply;

class ClickableLabel;

class DPodaci : public QDialog, private Ui::frmPodaci
{
    Q_OBJECT

public:
    explicit DPodaci(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~DPodaci(void);

    void setId(int id);

private:
    void setupGUI(void);

    ClickableLabel *m_lblSlika;

    int m_id;
    QNetworkAccessManager *m_networkManager;

private slots:
    void promenaNatpisa(void);
    void networkManagerFinished(QNetworkReply *reply);
    void lblSlikaOnClick(void);
    void snimi(void);
};

#endif // _W_PODACI_H_

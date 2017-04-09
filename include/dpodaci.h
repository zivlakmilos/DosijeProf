#ifndef _W_PODACI_H_
#define _W_PODACI_H_

#include <QDialog>
#include "ui_podaci.h"

class DPodaci : public QDialog, private Ui::frmPodaci
{
    Q_OBJECT

public:
    explicit DPodaci(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~DPodaci(void);

    void setId(int id);

private:
    void setupGUI(void);

    int m_id;

private slots:
    void promenaNatpisa(void);
};

#endif // _W_PODACI_H_

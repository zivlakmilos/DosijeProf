#ifndef _CENTRAL_WIDGET_H_
#define _CENTRAL_WIDGET_H_

#include <QWidget>

class QTableView;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~CentralWidget(void);

private:
    void setupGUI(void);

    QTableView *m_tblPodaci;
};

#endif // _CENTRAL_WIDGET_H_

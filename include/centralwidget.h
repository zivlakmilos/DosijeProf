#ifndef _CENTRAL_WIDGET_H_
#define _CENTRAL_WIDGET_H_

#include <QWidget>
#include <QModelIndex>

class QSqlQueryModel;
class QTableView;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~CentralWidget(void);

private:
    void setupGUI(void);

    QSqlQueryModel *m_modelPodaci;
    QTableView *m_tblPodaci;

private slots:
    void podaciOnDoubleClick(const QModelIndex &index);
};

#endif // _CENTRAL_WIDGET_H_

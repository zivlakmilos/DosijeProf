#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>

class CentralWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~MainWindow(void);

private:
    void setupActions(void);
    void setupMenu(void);
    void setupToolbar(void);

    CentralWidget *m_centralWidget;

    QAction *m_actionNoviFajl;
    QAction *m_actionObrisiFajl;
    QAction *m_actionIzlaz;

private slots:
    void noviFajlOnClick(void);
    void obrisiFajlOnClick(void);
};

#endif // _MAIN_WINDOW_H_

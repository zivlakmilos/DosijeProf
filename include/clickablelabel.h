#ifndef _CLICKABLE_LABEL_H_
#define _CLICKABLE_LABEL_H_

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = 0, Qt::WindowFlags f = 0)
        : QLabel(parent, f) {};
    explicit ClickableLabel(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0)
        : QLabel(text, parent, f) {};
    virtual ~ClickableLabel(void) {};

protected:
    virtual void mousePressEvent(QMouseEvent *ev)
    {
        if(ev->button() == Qt::LeftButton)
            emit clicked();
    };

signals:
    void clicked(void);
};

#endif // _CLICKABLE_LABEL_H_

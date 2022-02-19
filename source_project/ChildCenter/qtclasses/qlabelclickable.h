#ifndef QLABELCLICKABLE_H
#define QLABELCLICKABLE_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>

class QLabelClickable : public QLabel
{
    Q_OBJECT

public:
    QLabelClickable(QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void click();    
};

#endif // QLABELCLICKABLE_H

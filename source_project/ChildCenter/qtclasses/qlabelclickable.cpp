#include "qlabelclickable.h"

QLabelClickable::QLabelClickable(QWidget *parent):QLabel(parent)
{

}

void QLabelClickable::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton) emit click() ;
}

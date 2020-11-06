#include "restraintscrollareabg.h"

#include <QEvent>
#include <QPainter>
#include <QPaintEvent>

RestraintScrollAreaBg::RestraintScrollAreaBg(QWidget *p) : QWidget(p) {}
RestraintScrollAreaBg::~RestraintScrollAreaBg() {}

bool RestraintScrollAreaBg::event(QEvent *e)
{
    if (e->type() != QEvent::Type::Paint) {
        return QWidget::event(e);
    } else {
        return false;
    }
}

void RestraintScrollAreaBg::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(e->rect(), Qt::white);
}

#include "restraintscrollarea.h"

#include <QScrollBar>
#include "swipinggesture.h"

RestraintScrollArea::RestraintScrollArea(QWidget *parent) : QScrollArea(parent), TouchInterfacing(this)
{
    this->setViewport(nullptr);
    this->setFrameShape(QFrame::NoFrame);
}

bool RestraintScrollArea::handleOtherEvents(QEvent *e)
{
    return this->event(e);
}


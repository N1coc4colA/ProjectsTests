#include "restraintscrollarea.h"

#include <iostream>
#include <QScrollBar>
#include "swipinggesture.h"

RestraintScrollArea::RestraintScrollArea(QWidget *parent) : QScrollArea(parent), TouchInterfacing(this)
{
    this->setFrameShape(QFrame::NoFrame);
    //this->setBlockedEvents(SkipEvents::SwipeGesture);
}

bool RestraintScrollArea::handleSwipeGesture(SwipingGesture *swipe)
{
    std::cout << "Swipe gesture skiped" << std::endl;
    if (swipe->state() == Qt::GestureState::GestureFinished) {
        if (!this->horizontalScrollBar()->isHidden()) {
            std::cout << "Received swipe from scroll area" << std::endl;
        }
    }
    return false;
}

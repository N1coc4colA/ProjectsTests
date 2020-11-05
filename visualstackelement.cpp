#include "visualstackelement.h"
#include "swipinggesture.h"

#include <math.h>
#include <iostream>

VisualStackElement::VisualStackElement(QWidget *parent) : QStackedWidget(parent), TouchInterfacing(this) {}

VisualStackElement::~VisualStackElement()
{
    this->TouchInterfacing::~TouchInterfacing();
    this->QStackedWidget::~QStackedWidget();
}

bool VisualStackElement::handleOtherEvents(QEvent *e)
{
    return this->event(e);
}

bool VisualStackElement::handleSwipeGesture(SwipingGesture *gesture)
{

    int index = this->currentIndex();
    if (gesture->state() == Qt::GestureState::GestureFinished) {
        if (gesture->horizontalDirection() == QSwipeGesture::SwipeDirection::Right) {
            if ((index-1) > -1) {
                index--;
            } else {
                index = count()-1;
            }
        } else if (gesture->horizontalDirection() == QSwipeGesture::SwipeDirection::Left) {
            if ((index+1) < this->count()) {
                index++;
            } else {
                index = 0;
            }
        }
        this->setCurrentIndex(index);
        return true;
    } else {
        return false;
    }
}

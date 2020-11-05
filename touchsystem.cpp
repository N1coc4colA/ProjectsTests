#include "touchsystem.h"
#include "touchinterfacing.h"

#include <iostream>

#ifndef op
#define op(str) std::cout << str << std::endl;
bool operator == (const SkipEvents& y, const SkipEvents& x) { return ( (((x & y) == x)) ? true : false); }
bool operator != (const SkipEvents& y, const SkipEvents& x) { return !( (((x & y) == x)) ? true : false); }
#endif

TouchSystem::TouchSystem(TouchInterfacing *interface) : QObject(nullptr)
{
    this->interface = interface;
}

void TouchSystem::listenTo(QWidget *object)
{
    op("Installing event filter")
    object->installEventFilter(this);
}

void TouchSystem::check()
{
    if (!interface)
        this->~TouchSystem();
}

void TouchSystem::enableMergeModes(bool merge)
{
    this->merge = merge;
}

void TouchSystem::enableInternalHandling(bool enable)
{
    handling = enable;
}

void TouchSystem::enableSplitModesReceiving(bool enable)
{
    split = enable;
}

void TouchSystem::enableRejectToExternHandling(bool enable)
{
    reject = !enable;
}

bool TouchSystem::eventFilter(QObject *object, QEvent *event)
{
    check();
    bool out = false;
    if (!reject) {
        if (interface->skipEvents != SkipEvents::Any) {
            if (QWidget *source = qobject_cast<QWidget *>(object)) {
                if (event->type() == QEvent::Type::Gesture) {
                    if (interface->skipEvents != SkipEvents::GestureAll) {
                        if (processGestures(static_cast<QGestureEvent *>(event))) {
                            out = true;
                        }
                    }
                } else {
                    if (interface->skipEvents != SkipEvents::MouseAll) {
                        if (event->type() == QEvent::Type::MouseMove) {
                            if (processMouseMove(static_cast<QMouseEvent *>(event))) {
                                out = true;
                            }
                        } else if (event->type() == QEvent::Type::MouseButtonPress) {
                            if (processMousePress(static_cast<QMouseEvent *>(event))) {
                                out = true;
                            }
                        } else if (event->type() == QEvent::Type::MouseButtonRelease) {
                            if (processMouseRelease(static_cast<QMouseEvent *>(event))) {
                                out = true;
                            }
                        } else {
                            if (interface->skipEvents != SkipEvents::Other) {
                                return interface->handleOtherEvents(event);
                            }
                        }
                    }
                }
            }
        }
    }
    return out;
}

bool TouchSystem::processGestures(QGestureEvent *event)
{
    bool out = false;
    if (QGesture *swipe = event->gesture(Qt::SwipeGesture)) {
        if (interface->skipEvents != SkipEvents::SwipeGesture) {
            if (interface->handleSwipeGesture(new SwipingGesture(static_cast<QSwipeGesture *>(swipe)))) {
                out = true;
            }
        }
    } else if (QGesture *pan = event->gesture(Qt::PanGesture)) {
        if (interface->skipEvents != SkipEvents::PanGesture) {
            if (interface->handlePanGesture(static_cast<QPanGesture *>(pan))) {
                out = true;
            }
        }
    }

    if (QGesture *pinch = event->gesture(Qt::PinchGesture)) {
        if (interface->skipEvents != SkipEvents::PinchGesture) {
            if (interface->handlePinchGesture(static_cast<QPinchGesture *>(pinch))) {
                out = true;
            }
        }
    }
    if (QGesture *tap = event->gesture(Qt::TapGesture)) {
        if (interface->skipEvents != SkipEvents::TapGesture) {
            if (interface->handleTapGesture(static_cast<QTapGesture *>(tap))) {
                out = true;
            }
        }
    }

    return out;
}


bool TouchSystem::processMouseMove(QMouseEvent *e)
{
    if (merge) {
        if (press) {
            if (handling) {
                bool out = false;
                bool val1 = false;
                if (m_swipe) {
                    if (interface->skipEvents != SkipEvents::SwipeGesture) {
                        //Update the swipe
                        m_swipe->setSwipeAngle(generateAngle(*source, e->pos()));
                        m_swipe->setGestureState(Qt::GestureState::GestureUpdated);

                        //Calculate directions
                        QSwipeGesture::SwipeDirection dir = QSwipeGesture::SwipeDirection::Left;
                        if (source->x() < e->pos().x()) {
                            dir = QSwipeGesture::SwipeDirection::Right;
                        }
                        m_swipe->setHorizontalDirection(dir);
                        if (source->y() < e->pos().y()) {
                            dir = QSwipeGesture::SwipeDirection::Up;
                        } else {
                            dir = QSwipeGesture::SwipeDirection::Down;
                        }
                        m_swipe->setVerticalDirection(dir);

                        //Reupload
                        SwipingGesture *gest = new SwipingGesture;
                        memcpy((void *)gest, (void *)m_swipe, sizeof (*m_swipe));
                        val1 = interface->handleSwipeGesture(gest);
                        gest->~SwipingGesture();
                    }
                } else {
                    if (interface->skipEvents != SkipEvents::SwipeGesture) {
                        //Generate the swipe
                        m_swipe = new SwipingGesture();
                        //Calculate angle
                        m_swipe->setSwipeAngle(generateAngle(*source, e->pos()));
                        m_swipe->setGestureState(Qt::GestureState::GestureStarted);
                        //Upload event
                        SwipingGesture *gest = new SwipingGesture;
                        memcpy((void *)gest, (void *)m_swipe, sizeof (*m_swipe));
                        val1 = interface->handleSwipeGesture(gest);
                        gest->~SwipingGesture();
                    }
                }
                if (split) {
                    bool val2 = false;
                    if (interface->skipEvents != SkipEvents::MouseMove) {
                        val2 = interface->handleMouseMove(e);
                    }
                    if (val1 || val2) {
                        out = true;
                    }
                } else {
                    if ((!val1) && (interface->skipEvents != SkipEvents::MouseMove)) {
                        out = interface->handleMouseMove(e);
                    }
                }
                return out;
            }
        }
    }

    if (interface->skipEvents != SkipEvents::MouseMove) {
        return interface->handleMouseMove(e);
    }
    return false;
}

bool TouchSystem::processMousePress(QMouseEvent *e)
{
    if (merge) {
        if (e->button() == Qt::LeftButton) {
            press = true;
            source = new QPoint(e->pos());
            if (split) {
                if (interface->skipEvents != SkipEvents::MousePress) {
                    interface->handleMousePress(e);
                }
            }
            return true;
        }
    }
    if (interface->skipEvents != SkipEvents::MousePress) {
        interface->handleMousePress(e);
    }
    return false;
}

bool TouchSystem::processMouseRelease(QMouseEvent *e)
{
    if (merge) {
        if (e->button() == Qt::LeftButton) {
            press = false;
            if (e->pos() == *source) {
                bool val1 = false;

                if (interface->skipEvents != SkipEvents::TapGesture) {
                    //Means a click event, so generate a tap!
                    QTapGesture *gest = new QTapGesture;
                    gest->setPosition(e->pos());
                    gest->setHotSpot(e->globalPos());
                    source->~QPoint();
                    val1 = interface->handleTapGesture(gest);
                    gest->~QTapGesture();
                }

                if (split) {
                    if (val1 || interface->handleMouseRelease(e)) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return val1;
                }
            } else {
                if (m_swipe) {
                    //Clear the swipe
                    m_swipe->setGestureState(Qt::GestureState::GestureFinished);
                    SwipingGesture *tmp = new SwipingGesture;
                    memcpy((void *)tmp, (void *)m_swipe, sizeof (*m_swipe));
                    m_swipe->~SwipingGesture();

                    bool val1 = false;
                    if (interface->skipEvents != SkipEvents::SwipeGesture) {
                        val1 = interface->handleSwipeGesture(tmp);
                    }

                    if (split) {
                        if (val1) {
                            if ((interface->skipEvents != SkipEvents::MouseRelease) && interface->handleMouseRelease(e)) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            if (interface->skipEvents != SkipEvents::MouseRelease) {
                                return interface->handleMouseRelease(e);
                            }
                        }
                    }
                    return val1;
                }
            }
        }
    }
    if (interface->skipEvents != SkipEvents::MouseRelease) {
        return interface->handleMouseRelease(e);
    }
    return false;
}

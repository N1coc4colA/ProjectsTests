#include "touchinterfacing.h"

#include "touchsystem.h"

TouchInterfacing::TouchInterfacing(QWidget *source)
{
    this->source = source;

    source->grabGesture(Qt::GestureType::SwipeGesture);
    source->grabGesture(Qt::GestureType::PanGesture);
    source->grabGesture(Qt::GestureType::PinchGesture);
    source->grabGesture(Qt::GestureType::TapGesture);

    m_system = new TouchSystem(this);
    m_system->listenTo(source);
}

TouchInterfacing::~TouchInterfacing() {}

void TouchInterfacing::enableEventRedirection(bool enable)
{
    m_system->enableSplitModesReceiving(enable);
}

void TouchInterfacing::enableEventTranslation(bool enable)
{
    m_system->enableMergeModes(enable);
}

void TouchInterfacing::disableHandling(bool disable)
{
    m_system->enableInternalHandling(!disable);
}

void TouchInterfacing::enableInternalTasks(bool enable)
{
    m_system->enableInternalHandling(enable);
}

void TouchInterfacing::enableDebug(bool debug)
{
    m_system->enableDebug(debug);
}

void TouchInterfacing::setBlockedEvents(int events)
{
    skipEvents = events;
}

bool TouchInterfacing::handleOtherEvents(QEvent *) { return false; }
bool TouchInterfacing::handleSwipeGesture(SwipingGesture *) { return false; }
bool TouchInterfacing::handleTapGesture(QTapGesture *) { return false; }
bool TouchInterfacing::handlePinchGesture(QPinchGesture *) { return false; }
bool TouchInterfacing::handlePanGesture(QPanGesture *) { return false; }
bool TouchInterfacing::handleMousePress(QMouseEvent *) { return false; }
bool TouchInterfacing::handleMouseRelease(QMouseEvent *) { return false; }
bool TouchInterfacing::handleMouseMove(QMouseEvent *) { return false; }

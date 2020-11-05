#ifndef TOUCHINTERFACING_H
#define TOUCHINTERFACING_H

#include <QWidget>
#include <QGesture>
#include <math.h>

class TouchSystem;
class SwipingGesture;

enum SkipEvents {
    SwipeGesture = 0b00000000001,
    TapGesture =   0b00000000010,
    PinchGesture = 0b00000000100,
    PanGesture =   0b00000001000,
    MouseMove =    0b00000010000,
    MousePress =   0b00000100000,
    MouseRelease = 0b00001000000,
    MouseAll =     0b00010000000,
    GestureAll =   0b00100000000,
    Any =          0b01000000000,
    Other =        0b10000000000
};

class TouchInterfacing
{
public:
    TouchInterfacing(QWidget *source);
    virtual ~TouchInterfacing();

    /**
     * @brief Send mouse clicks to handleTapGesture directly or trigger the two
     * @param enable
     */
    void enableEventRedirection(bool enable = false);
    /**
     * @brief Translate some mouse events into gestures such as swipes
     * @param enable
     */
    void enableEventTranslation(bool enable = true);
    /**
     * @brief Disable use of proxy, no call are made to the handlers, they are sent to the target class
     * @param disable
     */
    void disableHandling(bool disable = true);
    /**
     * @brief Skip function calculations, such as the ones to calculate the swipe angle and the directions
     * @param enable
     */
    void enableInternalTasks(bool enable = true);
    /**
     * @brief Choose the events you won't process, they'll be skiped automatically.
     * @param events
     */
    void setBlockedEvents(int events);

protected:
    virtual bool handleSwipeGesture(SwipingGesture *gesture);
    virtual bool handleTapGesture(QTapGesture *gesture);
    virtual bool handlePinchGesture(QPinchGesture *gesture);
    virtual bool handlePanGesture(QPanGesture *gesture);
    virtual bool handleMousePress(QMouseEvent *event);
    virtual bool handleMouseRelease(QMouseEvent *event);
    virtual bool handleMouseMove(QMouseEvent *event);
    virtual bool handleOtherEvents(QEvent *e);

private:
    QWidget *source = nullptr;
    TouchSystem *m_system = nullptr;
    int skipEvents = 0;

    friend class TouchSystem;
};

inline static qreal generateAngle(QPoint source, QPoint target)
{
    QPoint middle(source.x(), target.y());
    int mt = target.x() - middle.x(), ms = middle.y() - source.y();
    double ts = sqrt(pow(ms, 2)+pow(mt, 2));
    return (0-asin(mt/ts));
}

#endif // TOUCHINTERFACING_H

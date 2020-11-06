#ifndef TOUCHSYSTEM_H
#define TOUCHSYSTEM_H

#include <QWidget>
#include <QGesture>
#include "swipinggesture.h"

class TouchInterfacing;

class TouchSystem : public QObject
{
    Q_OBJECT
public:
    explicit TouchSystem(TouchInterfacing *interface);

    bool eventFilter(QObject *object, QEvent *event) override;
    void listenTo(QWidget *object);

    /**
     * @brief Send possible synthetization of events from mouse to tablet events when handled.
     * @param merge
     */
    void enableMergeModes(bool merge);
    /**
     * @brief Send events to the source and synthetized targets.
     * @param enable
     */
    void enableSplitModesReceiving(bool enable);
    /**
     * @brief If enabled, it skips any internal calculations,
     * ignore any handling, leaving to the target object the handling instead of handling in this proxy.
     * @param enable
     */
    void enableInternalHandling(bool enable);
    /**
     * @brief Calls handlers without performing internal tasks
     * @param reject
     */
    void enableRejectToExternHandling(bool enable);
    /**
     * @brief Destroys the instance if the interface is no longer existent
     */
    void check();

    /**
     * @brief Prints events data when enabled with UID of the object
     * @param enable
     */
    void enableDebug(bool enable);

protected:
    bool processMouseMove(QMouseEvent *e);
    bool processMousePress(QMouseEvent *e);
    bool processMouseRelease(QMouseEvent *e);
    bool processGestures(QGestureEvent *event);

private:
    TouchInterfacing *interface;
    bool holding = false;
    bool press = false;
    bool merge = true;
    bool handling = true;
    bool split = false;
    bool reject = false;

    bool debug = false;

    int internal_id;
    inline static int getInternalID() {
        static int internal_identifier = 0;
        internal_identifier++;
        return internal_identifier;
    }

    QPoint *source = nullptr;
    QWidget *m_parent = nullptr;
    SwipingGesture *m_swipe = nullptr;
};

#endif // TOUCHSYSTEM_H

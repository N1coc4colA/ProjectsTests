#ifndef VISUALSTACKELEMENT_H
#define VISUALSTACKELEMENT_H

#include "touchinterfacing.h"
#include <QStackedWidget>

class VisualStackElement : public QStackedWidget, public TouchInterfacing
{
    Q_OBJECT
public:
    explicit VisualStackElement(QWidget *parent = nullptr);
    ~VisualStackElement() override;

protected:
    bool handleSwipeGesture(SwipingGesture *gesture) override;
    bool handleOtherEvents(QEvent *event) override;
};

#endif // VISUALSTACKELEMENT_H

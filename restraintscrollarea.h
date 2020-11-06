#ifndef RESTRAINTSCROLLAREA_H
#define RESTRAINTSCROLLAREA_H

#include <QScrollArea>
#include "touchinterfacing.h"

class RestraintScrollArea : public QScrollArea, public TouchInterfacing
{
public:
    RestraintScrollArea(QWidget *parent);

protected:
    bool handle;
    bool handleSwipeGesture(SwipingGesture *gest) override;
};

#endif // RESTRAINTSCROLLAREA_H

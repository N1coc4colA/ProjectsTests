#ifndef VISUALCATEGORY_H
#define VISUALCATEGORY_H

#include "structures.h"
#include "restraintscrollarea.h"

class QVBoxLayout;

class VisualCategory : public RestraintScrollArea
{
    Q_OBJECT
public:
    explicit VisualCategory(ListCategories *categories, QWidget *parent = nullptr);
    ListCategories *source;

protected:
    void paintEvent(QPaintEvent *) override;
    //bool event(QEvent *e) override;
    bool handleSwipeGesture(SwipingGesture *gest) override;
    QVBoxLayout *m_layout = nullptr;

private:
    void loadCategories();
};

#endif // VISUALCATEGORY_H

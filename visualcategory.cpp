#include "visualcategory.h"

#include "emptyitemdelegate.h"
#include "restraintscrollareabg.h"
#include "visualcategorylistelement.h"
#include "swipinggesture.h"
#include "visualstackelement.h"

#include <iostream>

#include <QEvent>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>

static const int m_width = 330;

VisualCategory::VisualCategory(ListCategories *src, QWidget *parent)
    : RestraintScrollArea(parent)
{
    source = src;

    this->setViewport(nullptr);
    this->setFrameShape(QFrame::NoFrame);
    this->setFixedWidth(m_width);

    QWidget *bg = new QWidget;
    m_layout = new QVBoxLayout;
    bg->setLayout(m_layout);
    bg->setFixedWidth(m_width);

    loadCategories();
    this->setWidget(bg);
    this->enableDebug(true);
}

bool VisualCategory::handleSwipeGesture(SwipingGesture *gest)
{
    if (VisualStackElement *stack = qobject_cast<VisualStackElement *>(parentWidget())) {
        if (gest->state() == Qt::GestureState::GestureFinished) {
            std::cout << "Swipe received from VisualCategory" << std::endl;
            return stack->handleSwipeGesture(gest);
        }
    }
    return RestraintScrollArea::handleSwipeGesture(gest);
}

/*bool VisualCategory::event(QEvent *e)
{
    //if (e->type() != QEvent::Type::MouseMove || e->type() != QEvent::MouseButtonPress || e->type() != QEvent::Type::MouseButtonRelease || e->type() != QEvent::Type::MouseButtonDblClick) {
    if (e->type() != ) {
        return false;
    } else {
        return QWidget::event(e);
    }
}*/

void VisualCategory::paintEvent(QPaintEvent *) {}

void VisualCategory::loadCategories()
{
    int i = 0;
    while (i<source->categories.length()) {
        VisualCategoryListElement *cat = new VisualCategoryListElement(source->categories.at(i), this);
        cat->setFixedWidth(m_width);
        m_layout->addWidget(cat);
        i++;
    }
}

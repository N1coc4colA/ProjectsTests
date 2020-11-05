#include "visualcategory.h"

#include "emptyitemdelegate.h"
#include "visualcategorylistelement.h"

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
}

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

#include "visualcategorylistelement.h"
#include "visuallistelement.h"

#include <iostream>
#include <QPainter>
#include <QResizeEvent>

#include <QDebug>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLine>

VisualCategoryListElement::VisualCategoryListElement(ListCategory *category, QWidget *parent)
    : QWidget(parent)
{
    source = category;
    m_layout = new FlowLayout;

    QHBoxLayout *lay = new QHBoxLayout;
    QVBoxLayout *mainL = new QVBoxLayout;
    container = new QWidget;
    QFrame *line = new QFrame;
    QLabel *iconic = new QLabel;
    QLabel *title = new QLabel;

    iconic->setPixmap(source->categoryIcon.pixmap(QSize(32, 32)));
    iconic->setFixedSize(32, 32);
    title->setText(source->categoryName);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    lay->addWidget(iconic);
    lay->addWidget(title);
    lay->addWidget(line);

    container->setLayout(lay);
    container->setFixedHeight(40);

    m_layout->setSpacing(10);
    m_layout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

    mainL->addWidget(container);
    mainL->addLayout(m_layout);
    mainL->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

    this->setLayout(mainL);
    this->resize(50,50);

    container->setAttribute(Qt::WA_TranslucentBackground, true);
    loadElements();
}

VisualCategoryListElement::~VisualCategoryListElement()
{
    m_layout->~FlowLayout();
}

void VisualCategoryListElement::paintEvent(QPaintEvent *) {}

void VisualCategoryListElement::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void VisualCategoryListElement::loadElements()
{
    int i = 0;
    while (i<source->elements.length()) {
        m_layout->addWidget(new VisualListElement(source->elements.at(i)));
        i++;
    }
}

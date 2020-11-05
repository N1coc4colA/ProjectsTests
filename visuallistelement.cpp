#include "visuallistelement.h"

#include <QPalette>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QPainterPath>

#include <iostream>

#define op(data) std::cout << data << std::endl;

static const int rected = 70; //Widget width, rected x rected is the area to paint the image
static const int bottomed = 20; //Bottom text height
static const int img_pad = 5; //Image void between widget limit and the image

VisualListElement::VisualListElement(ListElement *input, QWidget *parent) : QWidget(parent)
{
    source = input;
    this->setFixedSize(rected, rected+bottomed);
    this->setToolTip(source->name);
}

void VisualListElement::enterEvent(QEvent *e)
{
    hovered = true;
    QWidget::enterEvent(e);
    update();
}

void VisualListElement::leaveEvent(QEvent *e)
{
    hovered = false;
    QWidget::leaveEvent(e);
    update();
}

void VisualListElement::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::MouseButton::LeftButton) {
        clicked = true;
    } else {
        if (clicked) {
            clicked = false;
        }
    }
    QWidget::mousePressEvent(e);
    update();
}

void VisualListElement::mouseReleaseEvent(QMouseEvent *e)
{
    clicked = false;
    QWidget::mouseReleaseEvent(e);
    update();
}

void VisualListElement::paintEvent(QPaintEvent *e)
{
    if (source) {
        QPainter painter(this);
        QFont font = this->font();
        painter.setFont(font);
        painter.setOpacity(1);

        if (hovered == true) {
            QPainterPath path;
            path.addRoundedRect(this->rect(), 5, 5);
            if (clicked) {
                painter.fillPath(path, qApp->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Highlight));

                painter.setPen(qApp->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::HighlightedText));
                painter.setBrush(qApp->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::HighlightedText));
                painter.drawText(QRect(0, this->height() - bottomed, rected, bottomed), Qt::AlignmentFlag::AlignCenter, source->name);
            } else {
                QColor filled = qApp->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Shadow);
                filled.setAlpha(80);
                painter.fillPath(path, filled);

                painter.setPen(qApp->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Light));
                painter.setBrush(qApp->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Light));
                painter.drawText(QRect(0, this->height() - bottomed, rected, bottomed), Qt::AlignmentFlag::AlignCenter, source->name);
            }
        } else {
            painter.setPen(qApp->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Text));
            painter.drawText(QRect(0, this->height() - bottomed, rected, bottomed), Qt::AlignmentFlag::AlignCenter, source->name);
        }

        painter.drawPixmap(QRect(img_pad, img_pad, rected - img_pad*2, rected - img_pad*2), source->icon.pixmap(QSize(rected - img_pad*2, rected - img_pad*2)));
    } else {
        this->~VisualListElement();
    }
}

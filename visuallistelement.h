#ifndef VISUALLISTELEMENT_H
#define VISUALLISTELEMENT_H

#include <QWidget>
#include "structures.h"

class VisualListElement : public QWidget
{
    Q_OBJECT
public:
    explicit VisualListElement(ListElement *input, QWidget *parent = nullptr);
    ListElement *source = nullptr;

protected:
    void paintEvent(QPaintEvent *e) override;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

    bool hovered = false;
    bool clicked = false;
};

#endif // VISUALLISTELEMENT_H

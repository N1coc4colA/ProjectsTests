#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include "external/ScreenPage.hpp"

class Derivative : public ScreenPage
{
    Q_OBJECT
public:
    inline explicit Derivative(QColor col, QWidget *parent = nullptr) : ScreenPage(parent) {color = col;}

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QColor color = Qt::white;
};

#endif // DERIVATIVE_H

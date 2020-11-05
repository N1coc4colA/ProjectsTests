#include "derivative.h"

#include <QPainter>
#include <QPaintEvent>

void Derivative::paintEvent(QPaintEvent *e) {QPainter painter(this); painter.fillRect(e->rect(), color);}

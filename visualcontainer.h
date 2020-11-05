#ifndef VISUALCONTAINER_H
#define VISUALCONTAINER_H

#include <QWidget>

class VisualContainer : public QWidget
{
    Q_OBJECT
public:
    explicit VisualContainer(QWidget *parent = nullptr);
};

#endif // VISUALCONTAINER_H

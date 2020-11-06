#ifndef VISUALCATEGORYLISTELEMENT_H
#define VISUALCATEGORYLISTELEMENT_H

#include "flowlayout.h"
#include "structures.h"

#include <QWidget>

class VisualCategoryListElement : public QWidget
{
    Q_OBJECT
public:
    explicit VisualCategoryListElement(ListCategory *category, QWidget *parent = nullptr);
    ~VisualCategoryListElement();
    ListCategory *source;

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *e) override;
    bool event(QEvent *e) override;

private:
    FlowLayout *m_layout = nullptr;
    QWidget *container = nullptr;
    void loadElements();
};

#endif // VISUALCATEGORYLISTELEMENT_H

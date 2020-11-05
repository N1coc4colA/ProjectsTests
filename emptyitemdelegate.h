#ifndef EMPTYITEMDELEGATE_H
#define EMPTYITEMDELEGATE_H

#include <QItemDelegate>

class EmptyItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit EmptyItemDelegate(QObject *parent = nullptr);
    ~EmptyItemDelegate();
    void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const;
};


#endif // EMPTYITEMDELEGATE_H

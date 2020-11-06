#ifndef RESTRAINTSCROLLAREABG_H
#define RESTRAINTSCROLLAREABG_H

#include <QWidget>

class RestraintScrollAreaBg : public QWidget
{
    Q_OBJECT
public:
    explicit RestraintScrollAreaBg(QWidget *parent = nullptr);
    ~RestraintScrollAreaBg() override;

protected:
    bool event(QEvent *) override;
    void paintEvent(QPaintEvent *e) override;
};

#endif // RESTRAINTSCROLLAREABG_H

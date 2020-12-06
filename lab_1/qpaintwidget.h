#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QWidget>
#include <QPoint>

class myPaintWidget:public QWidget //наследуем класс от QWidget
{
    Q_OBJECT
public:
    myPaintWidget();
protected:
    void timerEvent(QTimerEvent*) override;
    void paintEvent(QPaintEvent *event) override;
private:
    void doDrawing();
    void move();
    int mytimer;
    int a = 65;
    QPoint func;
    void initMove();
};

#endif // QPAINTWIDGET_H

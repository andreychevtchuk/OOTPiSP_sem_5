#include "qpaintwidget.h"
#include <QtCore/qmath.h>
myPaintWidget::myPaintWidget()
{
    resize(600, 550);
    this->setStyleSheet("background-color:lightyellow;");
    initMove();
}

void myPaintWidget::timerEvent(QTimerEvent*)
{
    move();
    this->repaint();
}

void myPaintWidget::paintEvent(QPaintEvent*)
{
    doDrawing();//отрисовка
}

void myPaintWidget::doDrawing()
{
    QPainter text(this);
    text.setFont(QFont("Times New Roman",12));
    text.drawText(QPoint(270, 20), "Движение по Циссоиде Диокла");
    text.setPen(QPen(Qt::lightGray,1,Qt::SolidLine));
    text.setFont(QFont("Times New Roman",12,-1));
    text.rotate(-90);
    text.drawText(QPoint(-300, 20), "Графические примитивы в библиотеке QT");

    QPainter line(this);
    float i, j;
    for(i = 0; i<45; i++){
        j=qSqrt(i*i*i/(a-i));
        line.drawPoint(i+350, j+285);
        line.drawPoint(i+350, 285-j);
    }
    for(i = 45; i<60; i=i+0.5){
        j=qSqrt(i*i*i/(a-i));
        line.drawPoint(i+350, j+285);
        line.drawPoint(i+350, 285-j);
    }
    QPainter figure(this);
    QPolygonF polygon;
    polygon << QPoint(50+func.x(),func.y()) << QPoint(100+func.x(),80+func.y()) << QPoint(func.x(),80+func.y());
    figure.setBrush(Qt::blue);
    figure.drawPolygon(polygon);
    figure.setBrush(Qt::green);
    figure.drawEllipse(30+func.x(),25+func.y(), 40, 40);
}

void myPaintWidget::move()
{
    static int x=60, z, z2, x2;
    static float y;
    y=qSqrt(x*x*x/(a-x));
    func.rx() = x+300;
    func.ry() = y+240;
    if (x>0){
        x--;
        z=x;
    }
    if(x==0){
        y=-qSqrt(z*z*z/(a-z));
        func.rx() = z+300;
        func.ry() = y+240;
        if (z<60){
            z++;
            z2=z;
        }
        if(z>=60){
            y=-qSqrt(z2*z2*z2/(a-z2));
            func.rx() = z2+300;
            func.ry() = y+240;
            if(z2>0){
                z2--;
                x2=z2;
            }
            if (z2==0){
                y=qSqrt(x2*x2*x2/(a-x2));
                func.rx() = x2+300;
                func.ry() = y+240;
                x2++;
                if(x2==60){
                    x=60;
                }
            }
        }
    }
}
void myPaintWidget::initMove() {
    func.rx() = 200;
    func.ry() = 200;
    mytimer = startTimer(40); //будет через промежутки времени вызывать функцию-обработчик
}

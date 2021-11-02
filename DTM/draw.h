#ifndef DRAW_H
#define DRAW_H

#include <QWidget>

#include <QtGui>


class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint> points;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void clear();
    std::vector<QPoint> getPoints(){return points;}


signals:

public slots:
};

#endif // DRAW_H

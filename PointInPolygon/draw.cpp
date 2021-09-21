#include "draw.h"
#include <QtGui>


Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *event)
{
    // Create graphic object
    QPainter painter(this);
    painter.begin(this);

    //Create new polygon
    QPolygon pol;

    //Convert vector to polygon
    for (int i = 0; i < vertices.size(); i++){
        pol.append(vertices[i]);
    }

    //Draw polygon
    painter.drawPolygon(pol);

    //Improvements
    //for( QPoint vertex : vertices)
    //    pol.append(vertex);

    painter.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get cursor coordinates
    int x = event->pos().x();
    int y = event->pos().y();

    //Create new point
    QPoint p(x,y);

    //Add point to vector
    vertices.push_back(p);

    //Repaint screen
    repaint();
}

void Draw::clear()
{
    //Clear and repaint
    vertices.clear();
    repaint();
}

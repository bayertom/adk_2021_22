#include "algorithms.h"
#include <cmath>
#include "sortbyy.h"
#include "sortbyx.h"

#include <QtGui>

Algorithms::Algorithms()
{

}

double Algorithms::get2LinesAngle(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
{
    //Compute angle formed by two lines

    //Coordinate differences
    double ux=p2.x()-p1.x();
    double uy=p2.y()-p1.y();

    double vx=p4.x()-p3.x();
    double vy=p4.y()-p3.y();

    //Dot product
    double dp=ux*vx+uy*vy;

    //Norms
    double nu = sqrt(ux*ux + uy*uy);
    double nv = sqrt(vx*vx + vy*vy);

    //Angle
    return fabs(acos(dp/(nu*nv)));
}


QPolygon Algorithms::cHull (std::vector <QPoint> &points)
{
    QPolygon ch;

    //Sort points by y
    std::sort(points.begin(),points.end(),sortByY());

    //Find pivot
    QPoint q=points[0];

    //Add pivot to convex hull
    ch.append(q);

    //Create pj, pjj
    QPoint pj = q;
    QPoint pjj(0,q.y());

    do
    {
        int i_max = -1;
        double om_max = 0;
        //Find next point
        for (int i = 0; i<points.size(); i++)
        {
            double om = get2LinesAngle(pj, pjj, pj, points[i]);

            //Update maximum
            if (om > om_max)
            {
                om_max = om;
                i_max = i;
            }
        }

        //dd point to convex hull
        ch.append(points[i_max]);

        //Update points to next ones
        pjj=pj;
        pj=points[i_max];

    } while (pj != q);

    return ch;
}


std::vector <QPoint> Algorithms::rotate(std::vector <QPoint> &points, double sigma)
{
    //Rotate dataset by angle
    std::vector <QPoint> r_points;
    for (int i = 0; i < points.size(); i++)
    {
        //Rotate point
        double x_r = points[i].x()*cos(sigma) - points[i].y()*sin(sigma);
        double y_r = points[i].x()*sin(sigma) + points[i].y()*cos(sigma);

        // Create point
        QPoint rp(x_r, y_r);

        //Add point to the list
        r_points.push_back(rp);
    }

    return r_points;
}


std::tuple<std::vector<QPoint>, double> Algorithms::minMaxBox(std::vector <QPoint> &points)
{
    //Return vertices min max box and its area
    double area = 0;

    //Return min/max vertices
    QPoint pxmin = *std::min_element(points.begin(), points.end(), sortByX());
    QPoint pxmax = *std::max_element(points.begin(), points.end(), sortByX());
    QPoint pymin = *std::min_element(points.begin(), points.end(), sortByY());
    QPoint pymax = *std::max_element(points.begin(), points.end(), sortByY());

    //Create min max box vertices
    QPoint v1(pxmin.x(),pymin.y());
    QPoint v2(pxmax.x(),pymin.y());
    QPoint v3(pxmax.x(),pymax.y());
    QPoint v4(pxmin.x(),pymax.y());

    //Create min max box polygon
    std::vector<QPoint> mmb{v1,v2,v3,v4};

    //Calculate min max box area
    area = (pxmax.x()-pxmin.x())*(pymax.y()-pymin.y());

    return {mmb, area};
}


QPolygon Algorithms::minAreaEnclosingRectangle(std::vector <QPoint> &points)
{
    //Create minimum area enclosing rectangle
    QPolygon ch = cHull(points);

    //Searching for min max box with min area
    int n = ch.size();
    double sigma_min=0;
    std::vector<QPoint> mmb_min;

    //Initializing area_min
    auto [mmb, area_min] = minMaxBox(points);

    for (int i=0; i<n; i++)
    {
         //Coordinate differences
         double dx = ch[(i+1)%n].x() - ch[i].x();
         double dy = ch[(i+1)%n].y() - ch[i].y();

         double sigma = atan2(dy, dx);

         //Rotate by -sigma
         std::vector<QPoint> r_points = rotate(points, -sigma);

         //Create min max box
         auto [mmb, area] = minMaxBox(r_points);

         //Update minimum
         if (area < area_min)
         {
             area_min = area;
             sigma_min = sigma;
             mmb_min = mmb;
         }
     }

    //Create enclosing rectangle
    std::vector<QPoint> er = rotate(mmb_min, sigma_min);

    //Create QPolygon
    QPolygon er_pol;
    er_pol.append(er[0]);
    er_pol.append(er[1]);
    er_pol.append(er[2]);
    er_pol.append(er[3]);

    return er_pol;
}


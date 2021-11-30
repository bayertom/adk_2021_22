#ifndef TYPES_H
#define TYPES_H
#include <QtGui>
//#include "edge.h"

#include "qpointfbo.h"
class QPointFBO;

//Position of point and line
typedef enum{
    LeftHP,
    RightHP,
    On
} TPointLinePosition;

//Position of point and polygon
typedef enum{
    Inner,
    Outer,
    Boundary
} TPointPolygonPosition;

//Boolean operation
typedef enum {
    Union,
    Intersection,
    DifferenceA_B,
    DifferenceB_A
} TBooleanOperation;

//Position of line & line
typedef enum{
    Colinear,
    Parallel,
    Intersect,
    NonIntersect
} T2LinesPosition;

//Polygon
typedef std::vector<QPointFBO> TPolygon;

//Edges
//typedef  std::vector<Edge> TEdges;

#endif // TYPES_H

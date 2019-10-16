#ifndef POINT_H
#define POINT_H

#include <vector>
#include <QVector>

class Point
{
public:
    Point();
    Point(double,double, std::vector<double>);
    double x;
    double y;
    std::vector<double> Class;
};

#endif // POINT_H

#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
    double x;
    double y;
    int index;

    Point(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
        this->index = 0;
    }

    friend std::ostream& operator << (std::ostream& out, const Point& p);
};

#endif // POINT_H

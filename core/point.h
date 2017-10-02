#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Point
{
public:
    double x;
    double y;
    int index;

    Point(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
        this->index = 0;
    }

    const string str() const
    {
        stringstream ss;
        ss << '(' << x << ", " << y << ')';
        return ss.str();
    }

    friend std::ostream& operator << (std::ostream& out, const Point& p);
};

#endif // POINT_H

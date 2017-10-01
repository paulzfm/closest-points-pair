#ifndef POINT_H
#define POINT_H

class Point
{
public:
    double x;
    double y;

    Point(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
    }

    inline bool x_within_range(double left, double right) const {
        return left <= x && x <= right;
    }
};

#endif // POINT_H

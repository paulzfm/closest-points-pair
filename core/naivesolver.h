#ifndef NAIVESOLVER_H
#define NAIVESOLVER_H

#include "point.h"

#include <vector>
#include <tuple>
#include <math.h>

using std::vector;
using std::tuple;

#define SQ(x) ((x) * (x))

// straight-forward naive solver
// O(n^2)
class NaiveSolver
{
public:
    NaiveSolver(const vector<Point>& pts);

    // solve: returns the closest points pair with the distance
    tuple<tuple<Point, Point>, double> solve();

protected:
    vector<Point> input_points;

    // eudlic distance
    double distance(const Point& p1, const Point& p2)
    {
        return sqrt(SQ(p1.x - p2.x) + SQ(p1.y - p2.y));
    }
};

#endif // NAIVESOLVER_H

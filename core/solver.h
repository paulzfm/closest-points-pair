#ifndef SOLVER_H
#define SOLVER_H

#include "point.h"
#include <vector>
#include <tuple>

using std::vector;
using std::tuple;

#define SQ(x) ((x) * (x))

class Solver
{
public:
    Solver(vector<Point>& pts);

    tuple<tuple<Point, Point>, double> solve();

private:
    vector<Point >& input_points;
    vector<Point >& points_sorted_by_x;
    vector<Point >& points_sorted_by_y;

    tuple<tuple<Point, Point>, double> search(int left_most, int right_most);

    double distance(const Point& p1, const Point& p2)
    {
        return SQ(p1.x - p2.x) + SQ(p1.y - p2.y);
    }
};

#endif // SOLVER_H

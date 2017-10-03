#ifndef SOLVER_H
#define SOLVER_H

#include "naivesolver.h"

// optimal solver
// O(n lg n)
class Solver : NaiveSolver
{
public:
    Solver(const vector<Point>& pts);

    // solve: returns the closest points pair with the distance
    tuple<tuple<Point, Point>, double> solve();

private:
    vector<Point> points_sorted_by_x;
    vector<Point> points_sorted_by_y;

    tuple<tuple<Point, Point>, double> search(int left_most, int right_most, vector<Point>& pts);
};

#endif // SOLVER_H

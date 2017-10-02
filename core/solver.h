#ifndef SOLVER_H
#define SOLVER_H

#include "naivesolver.h"

class Solver : NaiveSolver
{
public:
    Solver(vector<Point>& pts);

    tuple<tuple<Point, Point>, double> solve();

private:
    vector<Point> points_sorted_by_x;
    vector<Point> points_sorted_by_y;

    tuple<tuple<Point, Point>, double> search(int left_most, int right_most, vector<Point>& pts);
};

#endif // SOLVER_H

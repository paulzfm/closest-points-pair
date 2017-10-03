#include "naivesolver.h"
#include "../utils.h"

using std::make_tuple;

NaiveSolver::NaiveSolver(const vector<Point>& pts)
    : input_points(pts)
{
}

tuple<tuple<Point, Point>, double> NaiveSolver::solve()
{
    double d = INF;
    Point p1, p2;

    int n = input_points.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double dis = distance(input_points[i], input_points[j]);
                if (dis < d) {
                    d = dis;
                    p1 = input_points[i];
                    p2 = input_points[j];
                }
            }
        }
    }

    return make_tuple(make_tuple(p1, p2), d);
}

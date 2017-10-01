#include "solver.h"

#include <algorithm>
#include <limits>
#include <math.h>
#include <assert.h>

using std::sort;
using std::tie;
using std::numeric_limits;
using std::make_tuple;

Solver::Solver(vector<Point>& pts)
    : input_points(pts), points_sorted_by_x(pts), points_sorted_by_y(pts)
{
    // initialize
    sort(points_sorted_by_x.begin(), points_sorted_by_x.end(),
         [](const Point& p1, const Point& p2) {
       return p1.x < p2.x;
    });
    sort(points_sorted_by_y.begin(), points_sorted_by_y.end(),
         [](const Point& p1, const Point& p2) {
       return p1.y < p2.y;
    });
}

tuple<tuple<Point, Point>, double> Solver::solve()
{
    double d;
    tuple<Point, Point> ps;
    tie(ps, d) = search(0, points_sorted_by_x.size() - 1);
    return make_tuple(ps, sqrt(d));
}

tuple<tuple<Point, Point>, double> Solver::search(int left_most, int right_most)
{
    // for base case
    if (left_most == right_most) {
        auto p = make_tuple(points_sorted_by_x[left_most], points_sorted_by_x[right_most]);
        return make_tuple(p, numeric_limits<double>::max());
    }

    // for recursive case
    assert(right_most - left_most + 1 >= 2);

    // 1. divide
    int mid = (left_most + right_most) / 2; // middle point index
    double mid_x = points_sorted_by_x[mid].x; // middle point x-coordinate

    // 2. conquer
    tuple<Point, Point> pl, pr;
    double dl, dr;
    tie(pl, dl) = search(left_most, mid);
    tie(pr, dr) = search(mid + 1, right_most);

    // 3. combine
    Point p1, p2; // currently minimal points pair
    double d; // currently minimal distance
    if (dl < dr) {
        d = dl;
        tie(p1, p2) = pl;
    } else {
        d = dr;
        tie(p1, p2) = pr;
    }

    vector<Point> pts;
    // filter candidate points
    for (const auto& p: points_sorted_by_y) {
        if (p.x_within_range(mid_x - d, mid_x + d)) {
            pts.push_back(p);
        }
    }
    // `pts` ONLY contains points whose x-coordinate is in range [`mid_x - d`, `mid_x + d`]

    int n = pts.size();
    for (int i = 0; i < n - 1; i++) { // for each candidate
        // find minimal distance by comparing the i-th point with its following 7 points
        double min = distance(pts[i], pts[i + 1]);
        int min_j = 1;
        for (int j = 2; j < 8; j++) {
            double dis = distance(pts[i], pts[i + j]);
            if (dis < min) {
                min = dis;
                min_j = j;
            }
        }
        // update if the new minimal distance is less than the currently minimal distance
        if (min < d) {
            d = min;
            p1 = pts[i];
            p2 = pts[i + min_j];
        }
    }
    // `d` stores the minimal distance for all points
    // whose x-coordinate is in range [`left_most`, `right_most`]

    return make_tuple(make_tuple(p1, p2), d);
}

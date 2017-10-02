#include "solver.h"
#include "../utils.h"

#include <algorithm>

using std::sort;
using std::tie;
using std::make_tuple;

Solver::Solver(vector<Point>& pts)
    : NaiveSolver(pts)
{
    // initialize
    points_sorted_by_x.insert(points_sorted_by_x.begin(), pts.begin(), pts.end());
    points_sorted_by_y.insert(points_sorted_by_y.begin(), pts.begin(), pts.end());

    // sort
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
    return search(0, input_points.size() - 1, points_sorted_by_y);
}

tuple<tuple<Point, Point>, double> Solver::search(int left_most, int right_most,
                                                  vector<Point>& pts)
{
    // for base case
    if (left_most == right_most) {
        auto p = make_tuple(points_sorted_by_x[left_most], points_sorted_by_x[right_most]);
        return make_tuple(p, INF);
    }
    if (left_most + 1 == right_most) {
        auto p = make_tuple(points_sorted_by_x[left_most], points_sorted_by_x[right_most]);
        return make_tuple(p,
                          distance(points_sorted_by_x[left_most], points_sorted_by_x[right_most]));
    }

    // for recursive case

    // 1. divide
    int mid = (left_most + right_most) / 2; // middle point index
    double mid_x = points_sorted_by_x[mid].x; // middle point x-coordinate

    // 2. conquer
    vector<Point> left_pts;
    vector<Point> right_pts;
    for (const auto& p: pts) { // classify points
        if (p.x <= mid_x) {
            left_pts.push_back(p);
        } else {
            right_pts.push_back(p);
        }
    }

    tuple<Point, Point> left_pair, right_pair;
    double left_dis, right_dis;
    tie(left_pair, left_dis) = search(left_most, mid, left_pts);
    tie(right_pair, right_dis) = search(mid + 1, right_most, right_pts);

    // 3. combine
    Point p1, p2; // currently minimal points pair
    double d; // currently minimal distance
    if (left_dis < right_dis) {
        d = left_dis;
        tie(p1, p2) = left_pair;
    } else {
        d = right_dis;
        tie(p1, p2) = right_pair;
    }

    vector<Point> candidates;
    // filter candidate points
    double left_bound = MAX(mid_x - d, points_sorted_by_x[left_most].x);
    double right_bound = MIN(mid_x + d, points_sorted_by_x[right_most].x);
    //cerr << "filter by [" << left_bound << ", " << right_bound << "]\n";
    for (const auto& p: pts) {
        if (left_bound <= p.x && p.x <= right_bound) {
            candidates.push_back(p);
        }
    }
    // `pts` ONLY contains points whose x-coordinate is in range [`mid_x - d`, `mid_x + d`]

    int n = candidates.size();
    for (int i = 0; i < n - 1; i++) { // for each candidate
        // find minimal distance by comparing the i-th point with its following 7 points
        double min = distance(candidates[i], candidates[i + 1]);
        int min_j = 1;
        for (int j = 2; (j < 8) && (i + j < n); j++) {
            double dis = distance(candidates[i], candidates[i + j]);
            if (dis < min) {
                min = dis;
                min_j = j;
            }
        }
        // update if the new minimal distance is less than the currently minimal distance
        if (min < d) {
            d = min;
            p1 = candidates[i];
            p2 = candidates[i + min_j];
        }
    }
    // `d` stores the minimal distance

    return make_tuple(make_tuple(p1, p2), d);
}

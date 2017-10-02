#include "randgen.h"

RandGen::RandGen()
    : gen(std::mt19937(rd()))
{
}

vector<Point> RandGen::generate(int size, double max_x, double max_y)
{
    std::uniform_real_distribution<> x_dist(0, max_x);
    std::uniform_real_distribution<> y_dist(0, max_y);

    vector<Point> pts;
    for (int i = 0; i < size; i++) {
        double x = x_dist(gen);
        double y = y_dist(gen);
        pts.push_back(Point(x, y));
    }

    return pts;
}

#ifndef RANDGEN_H
#define RANDGEN_H

#include "point.h"

#include <vector>
#include <random>

using std::vector;

// random point generator
class RandGen
{
public:
    RandGen();

    // generate `size` random points s.t. `x <= max_x & y <= max_y`
    vector<Point> generate(int size, double max_x, double max_y);

private:
    std::random_device rd;
    std::mt19937 gen;
};

#endif // RANDGEN_H

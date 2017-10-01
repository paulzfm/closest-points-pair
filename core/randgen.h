#ifndef RANDGEN_H
#define RANDGEN_H

#include "point.h"

#include <vector>
#include <random>

using std::vector;

class RandGen
{
public:
    RandGen();

    vector<Point> generate(int size, long long max_x, long long max_y);

private:
    int rand_int(int max);
    std::default_random_engine generator;
};

#endif // RANDGEN_H

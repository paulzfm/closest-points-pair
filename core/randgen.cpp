#include "randgen.h"

#include <util.h>
#include <assert.h>

using std::swap;

RandGen::RandGen()
{
}

vector<Point> RandGen::generate(int size, long long max_x, long long max_y)
{
    long long total = max_x * max_y;
    assert(size <= total);

    vector<Point> pts;
    for (long long x = 1; x <= max_x; x++) {
        for (long long y = 1; y <= max_y; y++) {
            pts.push_back(Point(x, y));
        }
    }
    for (long long i = 0; i < total; i++) {
        int idx = rand_int(total - 1);
        swap(pts[i], pts[idx]);
    }

    pts.resize(size);
    return pts;
}

int RandGen::rand_int(int max)
{
    std::uniform_int_distribution<int> distribution(0, max);
    return distribution(generator);
}

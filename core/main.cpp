#include <iostream>
#include <tuple>

#include "randgen.h"
#include "solver.h"

using std::tie;
using std::cerr;
using std::cout;

int main()
{
    int size = 1000000;
    RandGen rg;
    vector<Point> pts = rg.generate(size, 100000, 100000);

    clock_t start, end;
    Point p1, p2;
    double d;
    tuple<Point, Point> ps;

    double time1;
    if (size <= 50000) {
        start = clock();
        NaiveSolver nsolver(pts);
        tie(ps, d) = nsolver.solve();
        end = clock();
        tie(p1, p2) = ps;
        cerr << p1 << " -> " << p2 << " : " << d << "\n";
        time1 = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    }

    start = clock();
    Solver solver(pts);
    tie(ps, d) = solver.solve();
    end = clock();
    tie(p1, p2) = ps;
    cerr << p1 << " -> " << p2 << " : " << d << "\n";
    double time2 = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

    cerr << "naive=" << time1 << "ms\n";
    cerr << "opt=" << time2 << "ms\n";

    return 0;
}

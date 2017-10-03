#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <tuple>

#include "randgen.h"
#include "solver.h"

using std::tie;
using std::cout;

void print_usage(const char *name)
{
    fprintf(stderr, "Usage: %s [-f file|-r size max_x max_y] [o|b|a]\n", name);
    fprintf(stderr, "\t-f file        input points from `file`\n");
    fprintf(stderr, "\t               file format: n x_1 y_1 x_2 y_2 ... x_n y_n\n");
    fprintf(stderr, "\t-r size        generate `size` random points with maximum coordinate\n");
    fprintf(stderr, "\t               (`max_x`, `max_y`)\n");
    fprintf(stderr, "\to              solve with optimal algorithm (default)\n");
    fprintf(stderr, "\tb              solve with brute-force algorithm\n");
    fprintf(stderr, "\ta              solve with optimal and brute-force algorithm\n");
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }

    // input
    vector<Point> pts;
    int next;
    if (strcmp(argv[1], "-f") == 0) {
        next = 3;
    } else if (strcmp(argv[1], "-r") == 0) {
        if (argc < 5) {
            print_usage(argv[0]);
            return 1;
        }
        int size;
        double max_x, max_y;
        sscanf(argv[2], "%d", &size);
        sscanf(argv[3], "%lf", &max_x);
        sscanf(argv[4], "%lf", &max_y);

        RandGen rg;
        pts = rg.generate(size, max_x, max_y);
        next = 5;
    } else {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        return 1;
    }

    // algorithm selection
    int run_bf = 0;
    int run_opt = 0;
    if (next == argc) {
        run_opt = 1;
    } else {
        if (strcmp(argv[next], "o") == 0) {
            run_opt = 1;
        } else if (strcmp(argv[next], "b") == 0) {
            run_bf = 1;
        } else if (strcmp(argv[next], "a") == 0) {
            run_opt = 1;
            run_bf = 1;
        } else {
            fprintf(stderr, "Invalid argument: %s\n", argv[next]);
            return 1;
        }
    }

    // run algorithm
    clock_t start, end;
    Point p1, p2;
    double d;
    tuple<Point, Point> ps;
    double t;

    if (run_opt) {
        start = clock();
        Solver solver(pts);
        tie(ps, d) = solver.solve();
        end = clock();
        tie(p1, p2) = ps;
        t = (double) (end - start) / CLOCKS_PER_SEC * 1000.0;
        cout << "Optimal: closest points pair " << p1 << " and " << p2 << ", distance " << d
             << "\nOptimal: time (ms): " << t << "\n";
    }

    if (run_bf) {
        start = clock();
        NaiveSolver solver(pts);
        tie(ps, d) = solver.solve();
        end = clock();
        tie(p1, p2) = ps;
        t = (double) (end - start) / CLOCKS_PER_SEC * 1000.0;
        cout << "Brute-force: closest points pair " << p1 << " and " << p2 << ", distance " << d
             << "\nBrute-force: time (ms): " << t << "\n";
    }

    return 0;
}

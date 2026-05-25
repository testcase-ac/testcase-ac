#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long double sqr(long double x) {
    return x * x;
}

long double compute_volume(long double a, long double b, long double h) {
    const int steps = 10000;
    long double upper = sqrtl(h);
    long double dt = upper / steps;

    auto integrand = [&](long double t) {
        long double radius = a * expl(-sqr(t * t)) + b * t;
        return sqr(radius) * 2.0L * t;
    };

    long double sum = integrand(0.0L) + integrand(upper);

    for (int i = 1; i < steps; ++i) {
        long double t = dt * i;
        sum += (i % 2 == 0 ? 2.0L : 4.0L) * integrand(t);
    }

    return acosl(-1.0L) * sum * dt / 3.0L;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    double target_double = inf.readDouble(-1e300, 100000.0, "V");
    long double target = target_double;
    ensuref(target > 1.0L, "V must be greater than 1: %.17g", target_double);
    inf.readSpace();
    int n = inf.readInt(1, 5, "N");
    inf.readEoln();

    vector<long double> volumes;
    volumes.reserve(n);

    for (int i = 0; i < n; ++i) {
        double a_double = inf.readDouble(1.0, 10.0, "a");
        inf.readSpace();
        double b_double = inf.readDouble(1.0, 10.0, "b");
        inf.readSpace();
        double h_double = inf.readDouble(1.0, 10.0, "h");
        inf.readEoln();

        long double a = a_double;
        long double b = b_double;
        long double h = h_double;
        volumes.push_back(compute_volume(a, b, h));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long double diff = fabsl(volumes[i] - volumes[j]);
            ensuref(diff >= 1e-4L,
                    "volumes of vases %d and %d differ by %.12Lf", i, j, diff);

            long double target_diff_i = fabsl(volumes[i] - target);
            long double target_diff_j = fabsl(volumes[j] - target);
            long double target_diff_gap = fabsl(target_diff_i - target_diff_j);
            ensuref(target_diff_gap >= 1e-4L,
                    "target-volume differences for vases %d and %d differ by %.12Lf",
                    i, j, target_diff_gap);
        }
    }

    inf.readEof();
}

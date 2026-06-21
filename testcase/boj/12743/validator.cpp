#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Fraction {
    __int128 num;
    __int128 den;
};

int compareFraction(Fraction a, Fraction b) {
    __int128 lhs = a.num * b.den;
    __int128 rhs = b.num * a.den;
    if (lhs < rhs) return -1;
    if (lhs > rhs) return 1;
    return 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int x = inf.readInt(1, 1000000, "X");
    inf.readSpace();
    int y = inf.readInt(1, 1000000, "Y");
    inf.readEoln();

    vector<int> ga = inf.readInts(n, 1, 1000000, "GA_i");
    inf.readEoln();
    vector<int> gb = inf.readInts(n, 1, 1000000, "GB_i");
    inf.readEoln();
    vector<int> w = inf.readInts(n, 1, 1000000, "W_i");
    inf.readEoln();
    inf.readEof();

    int parallel = -1;
    Fraction bestParallel{0, 1};
    for (int i = 0; i < n; ++i) {
        if ((__int128)ga[i] * y != (__int128)gb[i] * x) continue;

        Fraction value{(__int128)w[i] * x, ga[i]};
        if (parallel == -1 || compareFraction(value, bestParallel) < 0) {
            parallel = i;
            bestParallel = value;
        }
    }

    if (parallel == -1) return 0;

    Fraction lo{0, 1};
    Fraction hi{bestParallel.num, bestParallel.den * x};

    for (int i = 0; i < n; ++i) {
        __int128 coef = (__int128)ga[i] * y - (__int128)gb[i] * x;
        __int128 rhs = (__int128)w[i] * y * bestParallel.den -
                       (__int128)gb[i] * bestParallel.num;

        if (coef == 0) {
            ensuref(rhs >= 0, "objective-parallel constraint %d is infeasible at the candidate optimum", i + 1);
            continue;
        }

        Fraction bound{rhs, coef * bestParallel.den};
        if (bound.den < 0) {
            bound.num = -bound.num;
            bound.den = -bound.den;
        }

        if (coef > 0) {
            if (compareFraction(bound, hi) < 0) hi = bound;
        } else {
            if (compareFraction(lo, bound) < 0) lo = bound;
        }
    }

    ensuref(compareFraction(lo, hi) >= 0,
            "maximum amounts are not unique: objective-parallel optimal segment remains feasible");
}

#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

static __int128 evalCubic(long long a, long long b, long long c, long long d,
                          long long x) {
    return (((__int128)a * x + b) * x + c) * x + d;
}

static vector<long long> integerRootCandidates(int d) {
    if (d == 0) {
        return {0};
    }

    vector<long long> roots;
    long long absD = llabs((long long)d);
    for (long long x = 1; x * x <= absD; ++x) {
        if (absD % x != 0) {
            continue;
        }
        roots.push_back(x);
        roots.push_back(-x);
        if (x * x != absD) {
            roots.push_back(absD / x);
            roots.push_back(-(absD / x));
        }
    }
    return roots;
}

static long double evalQuadratic(long double a, long double b, long double c,
                                 long double x) {
    return (a * x + b) * x + c;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 99, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        int a = inf.readInt(-2000000, 2000000, "A");
        inf.readSpace();
        int b = inf.readInt(-2000000, 2000000, "B");
        inf.readSpace();
        int c = inf.readInt(-2000000, 2000000, "C");
        inf.readSpace();
        int d = inf.readInt(-2000000, 2000000, "D");
        inf.readEoln();

        ensuref(a != 0, "case %d: A must be nonzero", tc);

        bool foundIntegerRoot = false;
        long long integerRoot = 0;
        for (long long candidate : integerRootCandidates(d)) {
            if (candidate < -1000000 || candidate > 1000000) {
                continue;
            }
            if (evalCubic(a, b, c, d, candidate) == 0) {
                foundIntegerRoot = true;
                integerRoot = candidate;
                break;
            }
        }
        ensuref(foundIntegerRoot, "case %d: no integer root in [-1000000, 1000000]", tc);

        long long qa = a;
        long long qb = (long long)b + qa * integerRoot;
        long long qc = (long long)c + qb * integerRoot;
        ensuref((__int128)d + (__int128)qc * integerRoot == 0,
                "case %d: internal synthetic division error", tc);

        vector<long double> roots;
        roots.push_back((long double)integerRoot);

        __int128 disc = (__int128)qb * qb - (__int128)4 * qa * qc;
        if (disc >= 0) {
            long double sqrtDisc = sqrt((long double)disc);
            long double denominator = 2.0L * qa;
            roots.push_back((-(long double)qb - sqrtDisc) / denominator);
            roots.push_back((-(long double)qb + sqrtDisc) / denominator);
        }

        sort(roots.begin(), roots.end());

        vector<long double> distinctRoots;
        for (long double root : roots) {
            if (distinctRoots.empty() ||
                fabsl(root - distinctRoots.back()) <= 1e-8L) {
                if (distinctRoots.empty()) {
                    distinctRoots.push_back(root);
                }
                continue;
            }
            distinctRoots.push_back(root);
        }

        const long double minRoot = -1000000.0L;
        const long double maxRoot = 1000000.0L;
        for (int i = 0; i < (int)distinctRoots.size(); ++i) {
            long double root = distinctRoots[i];
            ensuref(root >= minRoot && root <= maxRoot,
                    "case %d: real root %.12Lf is outside [-1000000, 1000000]",
                    tc, root);

            if (i + 1 < (int)distinctRoots.size()) {
                long double diff = distinctRoots[i + 1] - root;
                ensuref(diff > 1e-4L,
                        "case %d: distinct real roots %.12Lf and %.12Lf differ by %.12Lf",
                        tc, root, distinctRoots[i + 1], diff);
            }

            long double residual = fabsl(evalQuadratic((long double)qa, (long double)qb,
                                                       (long double)qc, root));
            ensuref(root == (long double)integerRoot || residual <= 1e-3L,
                    "case %d: internal quadratic reconstruction error", tc);
        }
    }

    inf.readEof();
    return 0;
}

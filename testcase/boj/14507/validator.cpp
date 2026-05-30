#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y, z;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_N = 4;
    const int MAX_N = 1000;
    const long long MIN_C = -1000;
    const long long MAX_C = 1000;

    int n = inf.readInt(MIN_N, MAX_N, "n");
    inf.readEoln();

    vector<Point> pts(n);
    set<tuple<long long,long long,long long>> seen;

    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(MIN_C, MAX_C, "x");
        inf.readSpace();
        long long y = inf.readLong(MIN_C, MAX_C, "y");
        inf.readSpace();
        long long z = inf.readLong(MIN_C, MAX_C, "z");
        inf.readEoln();

        auto key = make_tuple(x, y, z);
        ensuref(!seen.count(key),
                "Duplicate point at index %d: (%lld, %lld, %lld)",
                i, x, y, z);
        seen.insert(key);

        pts[i] = {x, y, z};
    }

    int N = n;
    auto tripleProductZero = [&](int i, int j, int k, int l) -> bool {
        long long ax = pts[j].x - pts[i].x;
        long long ay = pts[j].y - pts[i].y;
        long long az = pts[j].z - pts[i].z;
        long long bx = pts[k].x - pts[i].x;
        long long by = pts[k].y - pts[i].y;
        long long bz = pts[k].z - pts[i].z;
        long long cx = pts[l].x - pts[i].x;
        long long cy = pts[l].y - pts[i].y;
        long long cz = pts[l].z - pts[i].z;

        // scalar triple product (a x b) · c
        long long crossx = ay * bz - az * by;
        long long crossy = az * bx - ax * bz;
        long long crossz = ax * by - ay * bx;

        __int128 tp = (__int128)crossx * cx +
                      (__int128)crossy * cy +
                      (__int128)crossz * cz;
        return tp == 0;
    };

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            for (int k = j + 1; k < N; ++k) {
                for (int l = k + 1; l < N; ++l) {
                    ensuref(!tripleProductZero(i, j, k, l),
                            "Four coplanar stars detected at indices (%d, %d, %d, %d)",
                            i, j, k, l);
                }
            }
        }
    }

    inf.readEof();
}

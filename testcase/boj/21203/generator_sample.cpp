#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int COORD_MAX = 1000000;

int nearCoord(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(COORD_MAX, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 30);
    vector<pair<int, int>> points;
    points.reserve(n);

    if (mode == 0) {
        int groups = rnd.next(1, min(5, n));
        vector<pair<int, int>> bases;
        for (int i = 0; i < groups; ++i) {
            bases.emplace_back(rnd.next(1, COORD_MAX), rnd.next(1, COORD_MAX));
        }
        for (int i = 0; i < n; ++i) {
            points.push_back(rnd.any(bases));
        }
    } else if (mode == 1) {
        int street = rnd.next(1, COORD_MAX);
        for (int i = 0; i < n; ++i) {
            points.emplace_back(street, rnd.next(1, COORD_MAX));
        }
    } else if (mode == 2) {
        int avenue = rnd.next(1, COORD_MAX);
        for (int i = 0; i < n; ++i) {
            points.emplace_back(rnd.next(1, COORD_MAX), avenue);
        }
    } else if (mode == 3) {
        vector<pair<int, int>> corners = {
            {1, 1},
            {1, COORD_MAX},
            {COORD_MAX, 1},
            {COORD_MAX, COORD_MAX},
        };
        for (int i = 0; i < n; ++i) {
            pair<int, int> p = rnd.any(corners);
            if (rnd.next(4) == 0) {
                p.first = nearCoord(p.first, 3);
                p.second = nearCoord(p.second, 3);
            }
            points.push_back(p);
        }
    } else if (mode == 4) {
        int centerS = rnd.next(1, COORD_MAX);
        int centerA = rnd.next(1, COORD_MAX);
        int radius = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            points.emplace_back(nearCoord(centerS, radius), nearCoord(centerA, radius));
        }
    } else {
        int step = rnd.next(1, 1000);
        int startS = rnd.next(1, COORD_MAX);
        int startA = rnd.next(1, COORD_MAX);
        for (int i = 0; i < n; ++i) {
            int s = 1 + (startS - 1 + 1LL * i * step) % COORD_MAX;
            int a = 1 + (startA - 1 + 1LL * i * rnd.next(1, 1000)) % COORD_MAX;
            if (rnd.next(5) == 0) {
                s = rnd.next(1, COORD_MAX);
            }
            points.emplace_back(s, a);
        }
    }

    shuffle(points.begin(), points.end());

    println(n);
    for (auto p : points) {
        println(p.first, p.second);
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int CoordMax = 5000;

int boundedY(int value) {
    return max(0, min(CoordMax, value));
}

vector<int> randomDistinctXs(int n) {
    set<int> used;
    while ((int)used.size() < n) {
        used.insert(rnd.next(0, CoordMax));
    }
    return vector<int>(used.begin(), used.end());
}

vector<pair<int, int>> makeCase(int mode, int n) {
    vector<int> xs = randomDistinctXs(n);
    vector<pair<int, int>> points;
    points.reserve(n);

    int base = rnd.next(0, CoordMax);
    int amplitude = rnd.next(20, 2500);
    int slope = rnd.next(-6, 6);
    int phase = rnd.next(0, 360);

    for (int i = 0; i < n; ++i) {
        int y = 0;
        if (mode == 0) {
            y = rnd.next(0, CoordMax);
        } else if (mode == 1) {
            y = boundedY(base + slope * i + rnd.next(-3, 3));
        } else if (mode == 2) {
            y = (i % 2 == 0) ? rnd.next(0, 400) : rnd.next(4600, CoordMax);
        } else if (mode == 3) {
            y = rnd.next(0, 1) == 0 ? 0 : CoordMax;
        } else if (mode == 4) {
            int center = rnd.next(1000, 4000);
            y = boundedY(center + rnd.next(-80, 80));
        } else {
            double angle = (phase + i * 180.0 / max(1, n - 1)) * acos(-1.0) / 180.0;
            y = boundedY(base + (int)round(amplitude * sin(angle)));
        }
        points.emplace_back(xs[i], y);
    }

    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 14);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = caseIndex % 6;
        int n;
        if (caseIndex == 0) {
            n = 2;
        } else if (caseIndex == 1) {
            n = rnd.next(3, 8);
        } else if (caseIndex == t - 1 && rnd.next(0, 4) == 0) {
            n = rnd.next(128, 512);
        } else {
            n = rnd.next(8, 60);
        }

        vector<pair<int, int>> points = makeCase(mode, n);
        println(n);
        for (const auto& point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}

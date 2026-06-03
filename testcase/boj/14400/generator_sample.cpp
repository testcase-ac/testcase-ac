#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

constexpr int MIN_COORD = -1000000;
constexpr int MAX_COORD = 1000000;

int clampCoord(int value) {
    return max(MIN_COORD, min(MAX_COORD, value));
}

int nearCoord(int center, int radius) {
    return clampCoord(center + rnd.next(-radius, radius));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<pair<int, int>> points;

    if (mode == 0) {
        n = 1;
        points.push_back({rnd.next(MIN_COORD, MAX_COORD), rnd.next(MIN_COORD, MAX_COORD)});
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        int cx = rnd.next(-1000, 1000);
        int cy = rnd.next(-1000, 1000);
        int radius = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            points.push_back({nearCoord(cx, radius), nearCoord(cy, radius)});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        int fixed = rnd.next(MIN_COORD, MAX_COORD);
        bool vertical = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            int variable = rnd.next(-2000, 2000);
            if (vertical) {
                points.push_back({fixed, variable});
            } else {
                points.push_back({variable, fixed});
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        vector<int> coords = {MIN_COORD, MIN_COORD + 1, -1, 0, 1, MAX_COORD - 1, MAX_COORD};
        for (int i = 0; i < n; ++i) {
            points.push_back({rnd.any(coords), rnd.any(coords)});
        }
    } else if (mode == 4) {
        n = rnd.next(3, 35);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(-5000, 5000);
            int y = rnd.next(-5000, 5000);
            if (rnd.next(0, 1)) x = -x;
            if (rnd.next(0, 1)) y = -y;
            points.push_back({x, y});
        }
    } else {
        n = rnd.next(2, 60);
        int duplicateX = rnd.next(-100, 100);
        int duplicateY = rnd.next(-100, 100);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                points.push_back({duplicateX, duplicateY});
            } else {
                points.push_back({rnd.next(-10000, 10000), rnd.next(-10000, 10000)});
            }
        }
    }

    shuffle(points.begin(), points.end());

    println(n);
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}

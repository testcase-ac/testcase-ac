#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampInt(int value, int lo, int hi) {
    return max(lo, min(value, hi));
}

pair<int, int> randomPointNear(int cx, int cy, int xLimit, int yLimit, int radius) {
    int x = clampInt(cx + rnd.next(-radius, radius), 0, xLimit);
    int y = clampInt(cy + rnd.next(-radius, radius), 0, yLimit);
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int xLimit;
    int yLimit;
    int n;
    vector<pair<int, int>> points;

    if (mode == 0) {
        xLimit = rnd.next(1, 8);
        yLimit = rnd.next(1, 8);
        n = rnd.next(1, 12);

        vector<pair<int, int>> anchors = {
            {0, 0}, {xLimit, 0}, {0, yLimit}, {xLimit, yLimit},
            {rnd.next(0, xLimit), 0}, {0, rnd.next(0, yLimit)},
            {rnd.next(0, xLimit), yLimit}, {xLimit, rnd.next(0, yLimit)}
        };
        shuffle(anchors.begin(), anchors.end());
        for (int i = 0; i < n; ++i) {
            if (i < (int)anchors.size() && rnd.next(0, 99) < 75) {
                points.push_back(anchors[i]);
            } else {
                points.push_back({rnd.next(0, xLimit), rnd.next(0, yLimit)});
            }
        }
    } else if (mode == 1) {
        xLimit = rnd.next(2, 20);
        yLimit = rnd.next(2, 20);
        n = rnd.next(8, 35);

        int cx = rnd.next(0, xLimit);
        int cy = rnd.next(0, yLimit);
        int radius = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            points.push_back(randomPointNear(cx, cy, xLimit, yLimit, radius));
        }
    } else if (mode == 2) {
        xLimit = rnd.next(1, 12);
        yLimit = rnd.next(1, 12);
        n = rnd.next(5, 30);

        int baseCount = rnd.next(1, min(5, (xLimit + 1) * (yLimit + 1)));
        vector<pair<int, int>> bases;
        for (int i = 0; i < baseCount; ++i) {
            bases.push_back({rnd.next(0, xLimit), rnd.next(0, yLimit)});
        }
        for (int i = 0; i < n; ++i) {
            points.push_back(rnd.any(bases));
        }
    } else if (mode == 3) {
        xLimit = rnd.next(10, 60);
        yLimit = rnd.next(10, 60);
        n = rnd.next(10, 80);

        for (int i = 0; i < n; ++i) {
            points.push_back({rnd.next(0, xLimit), rnd.next(0, yLimit)});
        }
    } else if (mode == 4) {
        xLimit = rnd.next(1, 20);
        yLimit = rnd.next(1, 20);
        n = rnd.next(3, 50);

        bool vertical = rnd.next(0, 1);
        int fixed = vertical ? rnd.next(0, xLimit) : rnd.next(0, yLimit);
        for (int i = 0; i < n; ++i) {
            if (vertical) {
                points.push_back({fixed, rnd.next(0, yLimit)});
            } else {
                points.push_back({rnd.next(0, xLimit), fixed});
            }
        }
    } else {
        xLimit = rnd.any(vector<int>{1, 2, 999, 1000});
        yLimit = rnd.any(vector<int>{1, 2, 999, 1000});
        n = rnd.next(1, 25);

        vector<pair<int, int>> extremes = {
            {0, 0}, {xLimit, 0}, {0, yLimit}, {xLimit, yLimit},
            {xLimit / 2, yLimit / 2}
        };
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 60) {
                points.push_back(rnd.any(extremes));
            } else {
                points.push_back({rnd.next(0, xLimit), rnd.next(0, yLimit)});
            }
        }
    }

    println(xLimit, yLimit);
    println((int)points.size());
    for (auto point : points) {
        println(point.first, point.second);
    }

    return 0;
}

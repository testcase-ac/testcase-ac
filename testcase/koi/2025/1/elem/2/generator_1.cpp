#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode == 1) {
        n = rnd.next(3, 5);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 12);
    } else if (sizeMode == 3) {
        n = rnd.next(13, 25);
    } else {
        n = rnd.next(26, 60);
    }

    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    auto addPoint = [&](int x, int y) {
        if (used.insert({x, y}).second) {
            points.push_back({x, y});
        }
    };

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        int y = rnd.next(-20, 20);
        int start = rnd.next(-50, 50);
        int step = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            addPoint(start + i * step, y);
        }
    } else if (mode == 1) {
        int start = rnd.next(-40, 40);
        int step = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            int v = start + i * step;
            addPoint(v, v);
        }
    } else if (mode == 2) {
        vector<pair<int, int>> candidates;
        int w = rnd.next(3, 10);
        int h = rnd.next(3, 10);
        int ox = rnd.next(-20, 20);
        int oy = rnd.next(-20, 20);
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                candidates.push_back({ox + i, oy + j});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        n = min(n, (int)candidates.size());
        for (int i = 0; i < n; ++i) {
            addPoint(candidates[i].first, candidates[i].second);
        }
    } else if (mode == 3) {
        addPoint(-100000000, rnd.next(-10, 10));
        addPoint(100000000, rnd.next(-10, 10));
        addPoint(rnd.next(-10, 10), -100000000);
        addPoint(rnd.next(-10, 10), 100000000);
    } else if (mode == 4) {
        int baseX = rnd.next(-30, 30);
        int baseY = rnd.next(-30, 30);
        for (int i = 0; i < n; ++i) {
            int dx = rnd.next(-15, 15);
            int dy = rnd.next(-15, 15);
            addPoint(baseX + dx, baseY + dy);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(-100, 100);
            int y = rnd.next(-100, 100);
            addPoint(x, y);
        }
    }

    while ((int)points.size() < n) {
        int x = rnd.next(-1000, 1000);
        int y = rnd.next(-1000, 1000);
        addPoint(x, y);
    }

    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (auto [x, y] : points) {
        println(x, y);
    }
    return 0;
}

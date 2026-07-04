#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> allPoints() {
    vector<pair<int, int>> points;
    for (int x = 1; x <= 3; ++x) {
        for (int y = 1; y <= 4; ++y) {
            points.push_back({x, y});
        }
    }
    return points;
}

static int lengthForMode(int mode) {
    if (mode == 0) return rnd.any(vector<int>{1, 2, 3, 4});
    if (mode == 1) return rnd.any(vector<int>{997, 998, 999, 1000});
    if (mode == 2) return rnd.next(5, 20);
    if (mode == 3) return rnd.next(21, 80);
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    println(t);

    vector<pair<int, int>> points = allPoints();
    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        int l = lengthForMode(mode);
        int n;

        if (mode == 0) {
            n = rnd.next(0, 2);
        } else if (mode == 1) {
            n = rnd.next(0, 12);
        } else if (mode == 2) {
            n = rnd.next(8, 12);
        } else if (mode == 3) {
            n = rnd.next(3, 8);
        } else {
            n = rnd.next(0, 12);
        }

        vector<int> order(points.size());
        iota(order.begin(), order.end(), 0);

        if (mode == 2) {
            sort(order.begin(), order.end(), [&](int a, int b) {
                int da = abs(points[a].first - 2) + abs(points[a].second - 2);
                int db = abs(points[b].first - 2) + abs(points[b].second - 2);
                if (da != db) return da < db;
                return a < b;
            });
            int prefix = rnd.next(0, 3);
            shuffle(order.begin(), order.begin() + prefix);
            shuffle(order.begin() + prefix, order.end());
        } else if (mode == 3) {
            sort(order.begin(), order.end(), [&](int a, int b) {
                if (points[a].second != points[b].second) return points[a].second > points[b].second;
                return points[a].first < points[b].first;
            });
            if (rnd.next(0, 1)) reverse(order.begin(), order.end());
        } else {
            shuffle(order.begin(), order.end());
        }

        println(l, n);
        for (int i = 0; i < n; ++i) {
            auto [x, y] = points[order[i]];
            println(x, y);
        }
    }

    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<pair<int, int>> points;
    set<int> usedX;

    auto addPoint = [&](int x, int w) {
        if (x < 1 || x > 1000000000 || w < 1 || w > 1000000000) return false;
        if (!usedX.insert(x).second) return false;
        points.push_back({x, w});
        return true;
    };

    if (mode == 0) {
        int x = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            addPoint(x, rnd.next(1, 3));
            x += rnd.next(1, 5);
        }
    } else if (mode == 1) {
        int center = rnd.next(30, 120);
        for (int i = 0; i < n; ++i) {
            int x = center + i + rnd.next(0, 2);
            int w = rnd.next(10, 60);
            while (!addPoint(x, w)) ++x;
        }
    } else if (mode == 2) {
        int x = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 8);
            addPoint(x, w);
            x += w + rnd.next(1, 12) + rnd.next(1, 8);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, 200);
            int w = rnd.next(1, 120);
            while (!addPoint(x, w)) x = rnd.next(1, 200);
        }
    } else if (mode == 4) {
        vector<pair<int, int>> boundary = {
            {1, 1},
            {1000000000, 1},
            {999999999, 1000000000},
            {500000000, 1},
            {2, 999999999}
        };
        shuffle(boundary.begin(), boundary.end());
        for (auto p : boundary) {
            if ((int)points.size() == n) break;
            addPoint(p.first, p.second);
        }
        while ((int)points.size() < n) {
            int x = rnd.next(1, 1000000000);
            int w = rnd.next(1, 1000000000);
            addPoint(x, w);
        }
    } else {
        int clusters = rnd.next(2, 4);
        for (int c = 0; c < clusters && (int)points.size() < n; ++c) {
            int base = 1 + c * rnd.next(40, 90);
            int count = rnd.next(1, max(1, n / clusters + 2));
            for (int i = 0; i < count && (int)points.size() < n; ++i) {
                int x = base + rnd.next(0, 15);
                int w = rnd.next(1, 25);
                while (!addPoint(x, w)) ++x;
            }
        }
        while ((int)points.size() < n) {
            int x = rnd.next(1, 300);
            int w = rnd.next(1, 40);
            addPoint(x, w);
        }
    }

    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (auto p : points) {
        println(p.first, p.second);
    }

    return 0;
}

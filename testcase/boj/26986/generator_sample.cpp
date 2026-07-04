#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampCoord(int value) {
    return max(1, min(10000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int c;
    vector<int> xs;
    vector<int> ys;

    auto addPoint = [&](int x, int y) {
        xs.push_back(clampCoord(x));
        ys.push_back(clampCoord(y));
    };

    if (mode == 0) {
        n = rnd.next(1, 20);
        c = rnd.next(1, n);
        int x = rnd.next(1, 10000);
        int y = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                addPoint(x, y);
            } else {
                addPoint(x + rnd.next(-2, 2), y + rnd.next(-2, 2));
            }
        }
    } else if (mode == 1) {
        n = rnd.next(5, 35);
        c = rnd.next(2, n);
        int baseX = rnd.next(1, 9994);
        int baseY = rnd.next(1, 9994);
        int width = rnd.next(0, 6);
        int height = rnd.next(0, 6);
        for (int i = 0; i < n; ++i) {
            addPoint(baseX + rnd.next(0, width), baseY + rnd.next(0, height));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 28);
        c = rnd.next(2, n);
        int y = rnd.next(1, 10000);
        int start = rnd.next(1, 9950);
        int step = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            addPoint(start + i * step + rnd.next(0, 1), y + rnd.next(-1, 1));
        }
    } else if (mode == 3) {
        n = rnd.next(8, 45);
        c = rnd.next(2, n);
        for (int i = 0; i < n; ++i) {
            int side = rnd.next(0, 3);
            if (side == 0) addPoint(rnd.next(1, 20), rnd.next(1, 10000));
            if (side == 1) addPoint(rnd.next(9981, 10000), rnd.next(1, 10000));
            if (side == 2) addPoint(rnd.next(1, 10000), rnd.next(1, 20));
            if (side == 3) addPoint(rnd.next(1, 10000), rnd.next(9981, 10000));
        }
    } else if (mode == 4) {
        n = rnd.next(20, 70);
        c = rnd.next(3, n);
        int clusters = rnd.next(2, 5);
        vector<pair<int, int>> centers;
        for (int i = 0; i < clusters; ++i) {
            centers.push_back({rnd.next(5, 9996), rnd.next(5, 9996)});
        }
        for (int i = 0; i < n; ++i) {
            auto center = centers[rnd.next(0, clusters - 1)];
            addPoint(center.first + rnd.next(-4, 4), center.second + rnd.next(-4, 4));
        }
    } else {
        n = rnd.next(2, 60);
        c = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            addPoint(rnd.next(1, 10000), rnd.next(1, 10000));
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    println(c, n);
    for (int id : order) {
        println(xs[id], ys[id]);
    }

    return 0;
}

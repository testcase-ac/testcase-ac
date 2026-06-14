#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static const int LIM = 100000000;

static void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used,
                     int x, int y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

static void addUniqueRandom(vector<pair<int, int>>& points,
                            set<pair<int, int>>& used, int xLo, int xHi,
                            int yLo, int yHi) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int x = rnd.next(xLo, xHi);
        int y = rnd.next(yLo, yHi);
        if (!used.count({x, y})) {
            addPoint(points, used, x, y);
            return;
        }
    }

    for (int x = xLo; x <= xHi; ++x) {
        for (int y = yLo; y <= yHi; ++y) {
            if (!used.count({x, y})) {
                addPoint(points, used, x, y);
                return;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> points;
    set<pair<int, int>> used;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        addPoint(points, used, rnd.next(-10, 10), rnd.next(-10, 10));
    } else if (mode == 1) {
        int columns = rnd.next(2, 12);
        int baseX = rnd.next(-1000, 1000);
        int step = rnd.next(1, 20);
        for (int i = 0; i < columns; ++i) {
            int x = baseX + i * step;
            int low = rnd.next(-1000, 0);
            int high = rnd.next(0, 1000);
            if (low == high) ++high;
            addPoint(points, used, x, low);
            addPoint(points, used, x, high);

            int extra = rnd.next(0, 4);
            for (int j = 0; j < extra; ++j) {
                addUniqueRandom(points, used, x, x, low, high);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 40);
        int x = rnd.next(-5000, -1000);
        int y = rnd.next(-5000, 5000);
        int slope = rnd.next(-30, 30);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(1, 250);
            y += slope + rnd.next(-20, 20);
            y = max(-LIM, min(LIM, y));
            addPoint(points, used, x, y);
        }
    } else if (mode == 3) {
        addPoint(points, used, -LIM, -LIM);
        addPoint(points, used, -LIM, LIM);
        addPoint(points, used, LIM, -LIM);
        addPoint(points, used, LIM, LIM);
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) {
            int x = rnd.any(vector<int>{-LIM, LIM, rnd.next(-1000, 1000)});
            int y = rnd.any(vector<int>{-LIM, LIM, rnd.next(-1000, 1000)});
            addUniqueRandom(points, used, x, x, y, y);
        }
    } else if (mode == 4) {
        int clusters = rnd.next(2, 6);
        for (int c = 0; c < clusters; ++c) {
            int cx = rnd.next(-2000, 2000);
            int cy = rnd.next(-2000, 2000);
            int count = rnd.next(3, 12);
            for (int i = 0; i < count; ++i) {
                addUniqueRandom(points, used, cx - 15, cx + 15, cy - 15,
                                cy + 15);
            }
        }
    } else {
        int n = rnd.next(20, 120);
        int xSpan = rnd.next(1, 8);
        int ySpan = rnd.next(100, 5000);
        for (int i = 0; i < n; ++i) {
            addUniqueRandom(points, used, -xSpan, xSpan, -ySpan, ySpan);
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}

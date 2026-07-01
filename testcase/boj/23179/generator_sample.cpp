#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int randomColorNear(int base) {
    int delta = rnd.next(-2, 2);
    int color = base + delta;
    if (color < 1) color = 1;
    if (color > 100) color = 100;
    return color;
}

void addPoint(vector<pair<int, int>>& points, set<int>& used, int x, int color) {
    if (used.insert(x).second) {
        points.push_back({x, color});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<pair<int, int>> points;
    set<int> used;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        int start = rnd.next(-20, 20);
        int step = rnd.next(1, 5);
        int baseColor = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, start + i * step, randomColorNear(baseColor));
        }
    } else if (mode == 1) {
        int period = rnd.next(2, 12);
        int residues = rnd.next(1, min(period, 5));
        int base = rnd.next(-30, 30);
        for (int r = 0; r < residues; ++r) {
            int count = rnd.next(2, 4);
            int firstColor = rnd.next(1, 100);
            for (int k = 0; k < count; ++k) {
                int color = firstColor;
                if (k == count - 1 && rnd.next(0, 1)) {
                    color = firstColor == 100 ? 99 : firstColor + 1;
                }
                addPoint(points, used, base + r + k * period, color);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 10);
        int color = rnd.next(1, 100);
        int center = rnd.next(-100, 100);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, center + rnd.next(-40, 40), color);
        }
    } else if (mode == 3) {
        addPoint(points, used, -1000000000, rnd.next(1, 100));
        addPoint(points, used, 1000000000, rnd.next(1, 100));
        int n = rnd.next(3, 12);
        while ((int)points.size() < n) {
            int x = rnd.next(-100, 100);
            addPoint(points, used, x, rnd.next(1, 100));
        }
    } else {
        int n = rnd.next(15, 50);
        while ((int)points.size() < n) {
            int x = rnd.next(-200, 200);
            int color = rnd.next(1, 10);
            addPoint(points, used, x, color);
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (auto [x, color] : points) {
        println(x, color);
    }

    return 0;
}

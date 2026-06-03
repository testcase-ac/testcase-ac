#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    vector<pair<int, int>> points;
    set<int> used;

    auto addPoint = [&](int x, int color) {
        if (used.insert(x).second) {
            points.push_back({x, color});
        }
    };

    if (mode == 0) {
        int colors = rnd.next(1, 6);
        n = colors * 2;
        int base = rnd.next(0, 25);
        int step = rnd.next(2, 12);
        for (int color = 1; color <= colors; ++color) {
            int left = base + (color - 1) * step * 3;
            int gap = rnd.next(1, step);
            addPoint(left, color);
            addPoint(left + gap, color);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        int x = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(1, i % 3 == 0 ? 20 : 5);
            addPoint(x, 1);
        }
    } else if (mode == 2) {
        n = rnd.next(4, 20);
        if (n % 2 == 1) ++n;
        int x = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(1, 8);
            addPoint(x, (i % 2) + 1);
        }
    } else if (mode == 3) {
        int colors = rnd.next(2, 5);
        vector<int> sizes(colors, 2);
        int extra = rnd.next(0, 12);
        for (int i = 0; i < extra; ++i) {
            ++sizes[rnd.next(0, colors - 1)];
        }
        n = 0;
        int x = rnd.next(0, 20);
        for (int color = 1; color <= colors; ++color) {
            x += rnd.next(8, 20);
            for (int i = 0; i < sizes[color - 1]; ++i) {
                x += rnd.next(1, i == 0 ? 10 : 3);
                addPoint(x, color);
                ++n;
            }
        }
    } else {
        n = rnd.next(4, 14);
        if (n % 2 == 1) ++n;
        int colors = n / 2;
        for (int color = 1; color <= colors; ++color) {
            addPoint(color - 1, color);
            addPoint(100000 - (color - 1), color);
        }
    }

    n = (int)points.size();
    shuffle(points.begin(), points.end());

    println(n);
    for (auto [x, color] : points) {
        println(x, color);
    }

    return 0;
}

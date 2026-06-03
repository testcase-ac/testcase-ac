#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

const int MAX_COORD = 999999;

long long area2(const array<int, 6>& t) {
    return 1LL * (t[2] - t[0]) * (t[5] - t[1]) -
           1LL * (t[3] - t[1]) * (t[4] - t[0]);
}

array<int, 6> makeTriangle(int mode) {
    for (;;) {
        int base = mode == 1 ? rnd.next(0, 999990) : rnd.next(0, 40);
        int span = mode == 1 ? rnd.next(1, 9) : rnd.next(1, 12);

        if (mode == 2) {
            int x = rnd.next(0, 40);
            int y = rnd.next(0, 40);
            array<int, 6> t = {x, y, x + rnd.next(1, span), y,
                               x, y + rnd.next(1, span)};
            if (area2(t) != 0) return t;
        }

        if (mode == 3) {
            int x = rnd.next(0, 40);
            int y = rnd.next(0, 40);
            array<int, 6> t = {x, y, x + 1, y + span,
                               x + 2, y + rnd.next(0, span)};
            if (area2(t) != 0) return t;
        }

        int x1 = base + rnd.next(0, span);
        int y1 = base + rnd.next(0, span);
        int x2 = base + rnd.next(0, span);
        int y2 = base + rnd.next(0, span);
        int x3 = base + rnd.next(0, span);
        int y3 = base + rnd.next(0, span);

        array<int, 6> t = {x1, y1, x2, y2, x3, y3};
        if (area2(t) != 0) return t;
    }
}

int clampCoord(int x) {
    return max(0, min(MAX_COORD, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 18);
    int m = rnd.next(2, 24);
    int mode = rnd.next(0, 3);

    vector<array<int, 6>> triangles;
    for (int i = 0; i < n; ++i) {
        triangles.push_back(makeTriangle((mode + i) % 4));
    }

    vector<pair<char, int>> cuts;
    for (const auto& t : triangles) {
        int minX = min({t[0], t[2], t[4]});
        int maxX = max({t[0], t[2], t[4]});
        int minY = min({t[1], t[3], t[5]});
        int maxY = max({t[1], t[3], t[5]});

        if (minX < maxX) cuts.push_back({'x', rnd.next(minX + 1, maxX)});
        if (minY < maxY) cuts.push_back({'y', rnd.next(minY + 1, maxY)});
        cuts.push_back({'x', rnd.any(vector<int>{minX, maxX})});
        cuts.push_back({'y', rnd.any(vector<int>{minY, maxY})});
    }

    cuts.push_back({'x', 0});
    cuts.push_back({'y', MAX_COORD});
    while ((int)cuts.size() < m) {
        char axis = rnd.next(0, 1) == 0 ? 'x' : 'y';
        int c = mode == 1 ? rnd.next(999980, MAX_COORD) : rnd.next(0, 50);
        cuts.push_back({axis, c});
    }
    shuffle(cuts.begin(), cuts.end());
    cuts.resize(m);

    println(n);
    for (const auto& t : triangles) {
        println(t[0], t[1], t[2], t[3], t[4], t[5]);
    }
    println(m);
    for (const auto& [axis, c] : cuts) {
        println(string(1, axis), "=", clampCoord(c));
    }

    return 0;
}

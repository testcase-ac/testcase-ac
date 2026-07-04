#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

const int MIN_COORD = -10000;
const int MAX_COORD = 10000;

int clampCoord(int value) {
    return max(MIN_COORD, min(MAX_COORD, value));
}

int oddSize(int lo, int hi) {
    int n = rnd.next(lo, hi);
    if (n % 2 == 0) {
        if (n == hi) --n;
        else ++n;
    }
    return n;
}

pair<int, int> randomPoint() {
    return {rnd.next(MIN_COORD, MAX_COORD), rnd.next(MIN_COORD, MAX_COORD)};
}

vector<pair<int, int>> makeCase() {
    int mode = rnd.next(6);
    int n = oddSize(1, 25);
    vector<pair<int, int>> points;

    if (mode == 0) {
        n = 1;
        points.push_back(randomPoint());
    } else if (mode == 1) {
        int x = rnd.next(MIN_COORD, MAX_COORD);
        int y = rnd.next(MIN_COORD, MAX_COORD);
        n = oddSize(3, 19);
        for (int i = 0; i < n; ++i) points.push_back({x, y});
    } else if (mode == 2) {
        n = oddSize(3, 21);
        int x = rnd.next(MIN_COORD, MAX_COORD);
        int y0 = rnd.next(MIN_COORD + 50, MAX_COORD - 50);
        for (int i = 0; i < n; ++i) {
            int dy = rnd.next(-50, 50);
            points.push_back({x, y0 + dy});
        }
    } else if (mode == 3) {
        n = oddSize(5, 25);
        int need = n / 2 + 1;
        int baseX = rnd.next(MIN_COORD + 100, MAX_COORD - 100);
        int baseY = rnd.next(MIN_COORD + 100, MAX_COORD - 100);
        int width = rnd.next(1, 20);
        int height = rnd.next(1, 20);
        for (int i = 0; i < need; ++i) {
            points.push_back({baseX + rnd.next(0, width), baseY + rnd.next(0, height)});
        }
        while ((int)points.size() < n) {
            int side = rnd.next(4);
            if (side == 0) points.push_back({MIN_COORD, rnd.next(MIN_COORD, MAX_COORD)});
            if (side == 1) points.push_back({MAX_COORD, rnd.next(MIN_COORD, MAX_COORD)});
            if (side == 2) points.push_back({rnd.next(MIN_COORD, MAX_COORD), MIN_COORD});
            if (side == 3) points.push_back({rnd.next(MIN_COORD, MAX_COORD), MAX_COORD});
        }
    } else if (mode == 4) {
        n = oddSize(5, 17);
        vector<pair<int, int>> anchors = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
            {0, 0},
        };
        for (int i = 0; i < n; ++i) {
            auto anchor = rnd.any(anchors);
            points.push_back({clampCoord(anchor.first + rnd.next(-3, 3)),
                              clampCoord(anchor.second + rnd.next(-3, 3))});
        }
    } else {
        n = oddSize(7, 25);
        int range = rnd.next(5, 200);
        int baseX = rnd.next(MIN_COORD + range, MAX_COORD - range);
        int baseY = rnd.next(MIN_COORD + range, MAX_COORD - range);
        for (int i = 0; i < n; ++i) {
            points.push_back({baseX + rnd.next(-range, range),
                              baseY + rnd.next(-range, range)});
        }
    }

    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 8);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        vector<pair<int, int>> points = makeCase();
        println((int)points.size());
        for (auto point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}

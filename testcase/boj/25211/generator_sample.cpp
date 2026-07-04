#include "testlib.h"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

using namespace std;

struct PositiveRect {
    int x1;
    int y1;
    int x2;
    int y2;
};

PositiveRect makeRect(int mode) {
    int low = 1;
    int high = 12;
    int maxLen = 8;

    if (mode == 1) {
        high = 4;
        maxLen = 2;
    } else if (mode == 2) {
        high = 20;
        maxLen = 1;
    } else if (mode == 3) {
        low = rnd.next(50, 95);
        high = 100;
        maxLen = rnd.next(2, 12);
    } else if (mode == 4) {
        high = 30;
        maxLen = rnd.next(10, 35);
    }

    int x1 = rnd.next(low, high);
    int y1 = rnd.next(low, high);
    int x2 = min(100000, x1 + rnd.next(1, maxLen));
    int y2 = min(100000, y1 + rnd.next(1, maxLen));
    return {x1, y1, x2, y2};
}

array<int, 4> orient(int quadrant, const PositiveRect& rect) {
    if (quadrant == 1) return {rect.x1, rect.y1, rect.x2, rect.y2};
    if (quadrant == 2) return {-rect.x1, rect.y1, -rect.x2, rect.y2};
    if (quadrant == 3) return {-rect.x1, -rect.y1, -rect.x2, -rect.y2};
    return {rect.x1, -rect.y1, rect.x2, -rect.y2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        vector<PositiveRect> rects(4);

        if (mode == 0 && rnd.next(0, 1)) {
            PositiveRect base = makeRect(rnd.next(0, 2));
            for (int i = 0; i < 4; ++i) rects[i] = base;
        } else {
            for (int i = 0; i < 4; ++i) {
                int localMode = mode;
                if (rnd.next(0, 2) == 0) localMode = rnd.next(0, 4);
                rects[i] = makeRect(localMode);
            }
        }

        for (int quadrant = 1; quadrant <= 4; ++quadrant) {
            array<int, 4> line = orient(quadrant, rects[quadrant - 1]);
            println(line[0], line[1], line[2], line[3]);
        }
    }

    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
};

int coordNear(int lo, int hi) {
    return rnd.next(lo, hi);
}

Rect randomRect(int minCoord, int maxCoord) {
    int x1 = rnd.next(minCoord, maxCoord - 1);
    int x2 = rnd.next(x1 + 1, maxCoord);
    int y1 = rnd.next(minCoord, maxCoord - 1);
    int y2 = rnd.next(y1 + 1, maxCoord);
    return {x1, y1, x2, y2};
}

Rect clippedRect(int x1, int y1, int x2, int y2) {
    x1 = max(0, min(999, x1));
    y1 = max(0, min(999, y1));
    x2 = max(x1 + 1, min(1000, x2));
    y2 = max(y1 + 1, min(1000, y2));
    return {x1, y1, x2, y2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Rect> rects;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int n = rnd.next(1, 20);
        int bound = rnd.next(5, 25);
        for (int i = 0; i < n; ++i) {
            rects.push_back(randomRect(0, bound));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 18);
        int baseX = rnd.next(0, 40);
        int baseY = rnd.next(0, 40);
        int size = rnd.next(8, 35);
        for (int i = 0; i < n; ++i) {
            int shrink = min(size - 1, i + rnd.next(0, 2));
            rects.push_back(clippedRect(baseX + shrink, baseY + shrink, baseX + size, baseY + size));
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 24);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                int x = rnd.next(0, 999);
                int y1 = rnd.next(0, 999);
                int y2 = rnd.next(y1 + 1, 1000);
                rects.push_back({x, y1, x + 1, y2});
            } else {
                int y = rnd.next(0, 999);
                int x1 = rnd.next(0, 999);
                int x2 = rnd.next(x1 + 1, 1000);
                rects.push_back({x1, y, x2, y + 1});
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 25);
        int cx = rnd.next(0, 980);
        int cy = rnd.next(0, 980);
        for (int i = 0; i < n; ++i) {
            int x1 = coordNear(cx, cx + 12);
            int y1 = coordNear(cy, cy + 12);
            int x2 = coordNear(x1 + 1, cx + 20);
            int y2 = coordNear(y1 + 1, cy + 20);
            rects.push_back(clippedRect(x1, y1, x2, y2));
        }
    } else {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 5);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (rnd.next(0, 3) != 0) {
                    rects.push_back({c * 2, r * 2, c * 2 + rnd.next(1, 3), r * 2 + rnd.next(1, 3)});
                }
            }
        }
        if (rects.empty()) {
            rects.push_back({0, 0, 1, 1});
        }
    }

    shuffle(rects.begin(), rects.end());
    int n = (int)rects.size();
    int k = rnd.next(1, n);

    println(n, k);
    for (const Rect& rect : rects) {
        println(rect.x1, rect.y1, rect.x2, rect.y2);
    }

    return 0;
}

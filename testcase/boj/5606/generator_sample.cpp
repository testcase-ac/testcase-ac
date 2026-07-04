#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
};

static Rect makeRect(int x1, int y1, int x2, int y2) {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    if (x1 == x2) {
        if (x2 < 10000) ++x2;
        else --x1;
    }
    if (y1 == y2) {
        if (y2 < 10000) ++y2;
        else --y1;
    }
    return {x1, y1, x2, y2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Rect> rects;
    int mode = rnd.next(0, 5);
    int r = rnd.next(1, 2);

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int x1 = rnd.next(0, 9980);
            int y1 = rnd.next(0, 9980);
            int w = rnd.next(1, 20);
            int h = rnd.next(1, 20);
            rects.push_back(makeRect(x1, y1, min(10000, x1 + w), min(10000, y1 + h)));
        }
    } else if (mode == 1) {
        int n = rnd.next(3, 12);
        int baseX = rnd.next(0, 60);
        int baseY = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) {
            int x1 = baseX + rnd.next(0, 15);
            int y1 = baseY + rnd.next(0, 15);
            int x2 = baseX + rnd.next(12, 35);
            int y2 = baseY + rnd.next(12, 35);
            rects.push_back(makeRect(x1, y1, x2, y2));
        }
    } else if (mode == 2) {
        int rows = rnd.next(1, 4);
        int cols = rnd.next(2, 5);
        int cellW = rnd.next(1, 8);
        int cellH = rnd.next(1, 8);
        int startX = rnd.next(0, 30);
        int startY = rnd.next(0, 30);
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (rnd.next(0, 4) == 0) continue;
                int x1 = startX + x * cellW;
                int y1 = startY + y * cellH;
                rects.push_back(makeRect(x1, y1, x1 + cellW, y1 + cellH));
            }
        }
        if (rects.empty()) rects.push_back(makeRect(startX, startY, startX + cellW, startY + cellH));
    } else if (mode == 3) {
        int n = rnd.next(2, 8);
        int x1 = rnd.next(0, 20);
        int y1 = rnd.next(0, 20);
        int x2 = rnd.next(60, 100);
        int y2 = rnd.next(60, 100);
        for (int i = 0; i < n; ++i) {
            rects.push_back(makeRect(x1 + rnd.next(0, i * 3),
                                     y1 + rnd.next(0, i * 3),
                                     x2 - rnd.next(0, i * 3),
                                     y2 - rnd.next(0, i * 3)));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            int side = rnd.next(0, 3);
            int a = rnd.next(0, 9999);
            int b = rnd.next(a + 1, 10000);
            if (side == 0) rects.push_back(makeRect(0, a, rnd.next(1, 80), b));
            if (side == 1) rects.push_back(makeRect(a, 0, b, rnd.next(1, 80)));
            if (side == 2) rects.push_back(makeRect(10000 - rnd.next(1, 80), a, 10000, b));
            if (side == 3) rects.push_back(makeRect(a, 10000 - rnd.next(1, 80), b, 10000));
        }
    } else {
        int n = rnd.next(10, 30);
        int limit = rnd.next(20, 200);
        for (int i = 0; i < n; ++i) {
            int x1 = rnd.next(0, limit - 1);
            int y1 = rnd.next(0, limit - 1);
            int x2 = rnd.next(x1 + 1, limit);
            int y2 = rnd.next(y1 + 1, limit);
            rects.push_back({x1, y1, x2, y2});
        }
    }

    shuffle(rects.begin(), rects.end());
    println(static_cast<int>(rects.size()), r);
    for (const Rect& rect : rects) {
        println(rect.x1, rect.y1, rect.x2, rect.y2);
    }

    return 0;
}

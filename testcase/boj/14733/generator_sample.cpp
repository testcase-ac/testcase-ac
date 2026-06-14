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

Rect makeRect(int x1, int y1, int x2, int y2) {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    if (x1 == x2) ++x2;
    if (y1 == y2) ++y2;
    x1 = max(x1, -50000);
    y1 = max(y1, -50000);
    x2 = min(x2, 50000);
    y2 = min(y2, 50000);
    if (x1 >= x2) x1 = x2 - 1;
    if (y1 >= y2) y1 = y2 - 1;
    return {x1, y1, x2, y2};
}

void printRects(vector<Rect> rects) {
    shuffle(rects.begin(), rects.end());
    println(static_cast<int>(rects.size()));
    for (const Rect& r : rects) {
        println(r.x1, r.y1, r.x2, r.y2);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<Rect> rects;

    if (mode == 0) {
        int n = rnd.next(2, 12);
        int lo = rnd.next(-30, 0);
        int hi = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int x1 = rnd.next(lo, hi - 1);
            int x2 = rnd.next(x1 + 1, hi);
            int y1 = rnd.next(lo, hi - 1);
            int y2 = rnd.next(y1 + 1, hi);
            rects.push_back({x1, y1, x2, y2});
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 18);
        int left = rnd.next(-100, -20);
        int bottom = rnd.next(-100, -20);
        int right = rnd.next(20, 100);
        int top = rnd.next(20, 100);
        rects.push_back({left, bottom, right, top});
        for (int i = 1; i < n; ++i) {
            int shrink = rnd.next(0, 12);
            rects.push_back(makeRect(left + shrink, bottom + shrink, right - shrink, top - shrink));
        }
    } else if (mode == 2) {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 5);
        int cell = rnd.next(2, 10);
        int gap = rnd.next(0, 3);
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (rnd.next(0, 99) < 80) {
                    int x1 = x * (cell + gap);
                    int y1 = y * (cell + gap);
                    rects.push_back({x1, y1, x1 + cell, y1 + cell});
                }
            }
        }
        while (rects.size() < 2) {
            int x = rnd.next(0, cols - 1) * (cell + gap);
            int y = rnd.next(0, rows - 1) * (cell + gap);
            rects.push_back({x, y, x + cell, y + cell});
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                int x = rnd.next(-50000, 49999);
                rects.push_back(makeRect(x, -50000, x + rnd.next(1, 300), 50000));
            } else if (i % 3 == 1) {
                int y = rnd.next(-50000, 49999);
                rects.push_back(makeRect(-50000, y, 50000, y + rnd.next(1, 300)));
            } else {
                int x = rnd.next(-50000, 49990);
                int y = rnd.next(-50000, 49990);
                rects.push_back(makeRect(x, y, x + rnd.next(1, 10), y + rnd.next(1, 10)));
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 120);
        int span = rnd.next(40, 400);
        for (int i = 0; i < n; ++i) {
            int x1 = -span + i;
            int y1 = rnd.next(-span, span - 1);
            int x2 = x1 + rnd.next(1, span);
            int y2 = rnd.next(y1 + 1, span);
            rects.push_back(makeRect(x1, y1, x2, y2));
        }
    } else {
        int n = rnd.next(500, 3000);
        int base = rnd.next(-50000, -47000);
        for (int i = 0; i < n; ++i) {
            int x1 = base + i % 3000;
            int y1 = -50000 + (i * 37) % 97000;
            int w = rnd.next(1, 2000);
            int h = rnd.next(1, 2000);
            rects.push_back(makeRect(x1, y1, x1 + w, y1 + h));
        }
    }

    printRects(rects);
    return 0;
}

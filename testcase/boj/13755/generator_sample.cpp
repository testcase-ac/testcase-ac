#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

using Rect = pair<int, int>;

static void maybeRotate(Rect& r) {
    if (rnd.next(2) == 1) swap(r.first, r.second);
}

static void printRects(vector<Rect> rects) {
    shuffle(rects.begin(), rects.end());
    for (Rect& r : rects) {
        maybeRotate(r);
        println(r.first, r.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    vector<Rect> rects;

    if (mode == 0) {
        int side = rnd.next(3, 100);
        int a = rnd.next(1, side - 2);
        int b = rnd.next(1, side - a - 1);
        int c = side - a - b;
        rects = {{side, a}, {side, b}, {side, c}};
    } else if (mode == 1) {
        int side = rnd.next(2, 100);
        int leftWidth = rnd.next(1, side - 1);
        int rightWidth = side - leftWidth;
        int topHeight = rnd.next(1, side - 1);
        int bottomHeight = side - topHeight;
        rects = {{leftWidth, side}, {rightWidth, topHeight}, {rightWidth, bottomHeight}};
    } else if (mode == 2) {
        int side = rnd.next(2, 100);
        int fullHeight = rnd.next(1, side - 1);
        int bottomHeight = side - fullHeight;
        int leftWidth = rnd.next(1, side - 1);
        int rightWidth = side - leftWidth;
        rects = {{side, fullHeight}, {leftWidth, bottomHeight}, {rightWidth, bottomHeight}};
    } else if (mode == 3) {
        int side = rnd.next(3, 100);
        int a = rnd.next(1, side - 2);
        int b = rnd.next(1, side - a - 1);
        int c = side - a - b;
        rects = {{side, a}, {side, b}, {side, c}};
        int idx = rnd.next(3);
        int delta = rnd.next(2) == 0 ? -1 : 1;
        if (rects[idx].second + delta < 1 || rects[idx].second + delta > 100) delta = -delta;
        rects[idx].second += delta;
    } else if (mode == 4) {
        int base = rnd.next(1, 95);
        int height = rnd.next(1, 95);
        int gap = rnd.next(1, 5);
        rects = {{base, height}, {base + gap, height}, {base, height + gap}};
    } else {
        for (int i = 0; i < 3; ++i) {
            int w = rnd.next(1, 100);
            int h = rnd.next(1, 100);
            rects.push_back({w, h});
        }
    }

    printRects(rects);
    return 0;
}

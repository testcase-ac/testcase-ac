#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int kMaxCoord = 998244352;

struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
};

int bounded(int value) {
    return max(0, min(kMaxCoord, value));
}

pair<int, int> makeInterval(int start, int len) {
    start = bounded(start);
    int end = bounded(start + max(1, len));
    if (end <= start) {
        start = max(0, end - 1);
    }
    return {start, end};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 60 : 18);
    vector<Rect> rects;
    rects.reserve(n);

    if (mode == 0) {
        int baseX = rnd.next(0, 30);
        int baseY = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            int x1 = baseX + rnd.next(0, 8);
            int y1 = baseY + rnd.next(0, 8);
            rects.push_back({x1, y1, x1 + rnd.next(1, 12), y1 + rnd.next(1, 12)});
        }
    } else if (mode == 1) {
        int x = rnd.next(0, 5);
        int y = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 5);
            int h = rnd.next(1, 5);
            rects.push_back({x, y, x + w, y + h});
            x += w + rnd.next(1, 8);
            y += h + rnd.next(1, 8);
        }
    } else if (mode == 2) {
        int x = rnd.next(0, 10);
        int y = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 7);
            int h = rnd.next(1, 7);
            rects.push_back({x, y, x + w, y + h});
            x += w;
            y += rnd.next(0, 2) == 0 ? h : rnd.next(0, 3);
        }
    } else if (mode == 3) {
        int outer = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int margin = rnd.next(0, min(i + 5, outer - 1));
            int x1 = margin;
            int y1 = rnd.next(0, margin + 3);
            int x2 = outer - rnd.next(0, margin);
            int y2 = outer - rnd.next(0, margin);
            if (x1 >= x2) x2 = x1 + 1;
            if (y1 >= y2) y2 = y1 + 1;
            rects.push_back({x1, y1, x2, y2});
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int anchor = rnd.next(0, 1) == 0 ? rnd.next(0, 50) : kMaxCoord - rnd.next(0, 50);
            int xLen = rnd.next(1, 20);
            int yLen = rnd.next(1, 20);
            auto x = makeInterval(anchor - rnd.next(0, xLen), xLen);
            auto y = makeInterval(kMaxCoord - anchor - rnd.next(0, yLen), yLen);
            rects.push_back({x.first, y.first, x.second, y.second});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int x1 = rnd.next(0, 120);
            int y1 = rnd.next(0, 120);
            int shape = rnd.next(0, 2);
            int w = shape == 0 ? 1 : rnd.next(2, 30);
            int h = shape == 1 ? 1 : rnd.next(2, 30);
            rects.push_back({x1, y1, x1 + w, y1 + h});
        }
    }

    shuffle(rects.begin(), rects.end());

    println(static_cast<int>(rects.size()));
    for (const Rect& r : rects) {
        println(r.x1, r.y1, r.x2, r.y2);
    }

    return 0;
}

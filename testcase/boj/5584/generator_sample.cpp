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

static Rect randomRectAvoidingOrigin(int w, int h) {
    while (true) {
        int x1 = rnd.next(0, w - 1);
        int y1 = rnd.next(0, h - 1);
        int x2 = rnd.next(x1 + 1, w);
        int y2 = rnd.next(y1 + 1, h);
        if (x1 != 0 || y1 != 0) {
            return {x1, y1, x2, y2};
        }
    }
}

static Rect verticalStripAvoidingOrigin(int w, int h) {
    int x1 = rnd.next(1, w - 1);
    int x2 = rnd.next(x1 + 1, w);
    int y1 = rnd.next(0, h - 1);
    int y2 = rnd.next(y1 + 1, h);
    return {x1, y1, x2, y2};
}

static Rect horizontalStripAvoidingOrigin(int w, int h) {
    int x1 = rnd.next(0, w - 1);
    int x2 = rnd.next(x1 + 1, w);
    int y1 = rnd.next(1, h - 1);
    int y2 = rnd.next(y1 + 1, h);
    return {x1, y1, x2, y2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int w;
    int h;
    int n;
    vector<Rect> rects;

    if (mode == 0) {
        w = rnd.next(2, 15);
        h = rnd.next(2, 15);
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            rects.push_back(randomRectAvoidingOrigin(w, h));
        }
    } else if (mode == 1) {
        w = rnd.next(5, 30);
        h = rnd.next(5, 30);
        n = rnd.next(4, 18);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(2) == 0) {
                rects.push_back(verticalStripAvoidingOrigin(w, h));
            } else {
                rects.push_back(horizontalStripAvoidingOrigin(w, h));
            }
        }
    } else if (mode == 2) {
        w = rnd.next(8, 40);
        h = rnd.next(8, 40);
        n = rnd.next(8, 30);
        int splitX = rnd.next(2, w - 2);
        int splitY = rnd.next(2, h - 2);
        for (int i = 0; i < n; ++i) {
            int side = rnd.next(4);
            if (side == 0) {
                int y1 = rnd.next(0, h - 1);
                rects.push_back({splitX, y1, rnd.next(splitX + 1, w), rnd.next(y1 + 1, h)});
            } else if (side == 1) {
                int x1 = rnd.next(0, w - 1);
                rects.push_back({x1, splitY, rnd.next(x1 + 1, w), rnd.next(splitY + 1, h)});
            } else if (side == 2) {
                rects.push_back(verticalStripAvoidingOrigin(w, h));
            } else {
                rects.push_back(horizontalStripAvoidingOrigin(w, h));
            }
        }
    } else {
        w = rnd.next(1000, 1000000);
        h = rnd.next(1000, 1000000);
        n = rnd.next(5, 25);
        for (int i = 0; i < n; ++i) {
            rects.push_back(randomRectAvoidingOrigin(w, h));
        }
    }

    shuffle(rects.begin(), rects.end());

    println(w, h);
    println(static_cast<int>(rects.size()));
    for (const Rect& r : rects) {
        println(r.x1, r.y1, r.x2, r.y2);
    }

    return 0;
}

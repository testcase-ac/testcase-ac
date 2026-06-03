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

Rect makeRect(int x1, int y1, int w, int h) {
    return {x1, y1, x1 + w, y1 - h};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Rect> rects;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(-20, 20);
            int y = rnd.next(-20, 20);
            rects.push_back(makeRect(x, y, rnd.next(1, 8), rnd.next(1, 8)));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 16);
        int cx = rnd.next(-10, 10);
        int cy = rnd.next(-10, 10);
        for (int i = 0; i < n; ++i) {
            int left = cx - rnd.next(1, 10);
            int top = cy + rnd.next(1, 10);
            int right = cx + rnd.next(1, 10);
            int bottom = cy - rnd.next(1, 10);
            rects.push_back({left, top, right, bottom});
        }
    } else if (mode == 2) {
        int rows = rnd.next(1, 4);
        int cols = rnd.next(2, 5);
        int cell = rnd.next(2, 7);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int jitterX = rnd.next(-1, 1);
                int jitterY = rnd.next(-1, 1);
                int x = c * cell + jitterX;
                int y = -r * cell + jitterY;
                rects.push_back(makeRect(x, y, rnd.next(1, cell + 2), rnd.next(1, cell + 2)));
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 14);
        int x = rnd.next(-30, -5);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 8);
            int gap = rnd.next(0, 3);
            int top = rnd.next(-5, 15);
            int height = rnd.next(1, 12);
            rects.push_back(makeRect(x, top, w, height));
            x += w + gap;
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 10);
        int left = rnd.next(-15, 5);
        int top = rnd.next(5, 20);
        int width = rnd.next(8, 20);
        int height = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            int shrinkLeft = rnd.next(0, width - 1);
            int shrinkRight = rnd.next(0, width - shrinkLeft - 1);
            int shrinkTop = rnd.next(0, height - 1);
            int shrinkBottom = rnd.next(0, height - shrinkTop - 1);
            rects.push_back({left + shrinkLeft, top - shrinkTop,
                             left + width - shrinkRight, top - height + shrinkBottom});
        }
    } else {
        int n = rnd.next(2, 8);
        rects.push_back({-100000000, 100000000, rnd.next(-10, 10), rnd.next(-10, 10)});
        rects.push_back({rnd.next(-10, 10), rnd.next(-10, 10), 100000000, -100000000});
        for (int i = 2; i < n; ++i) {
            int x = rnd.next(-50, 50);
            int y = rnd.next(-50, 50);
            rects.push_back(makeRect(x, y, rnd.next(1, 25), rnd.next(1, 25)));
        }
    }

    shuffle(rects.begin(), rects.end());

    println(static_cast<int>(rects.size()));
    for (const Rect& rect : rects) {
        println(rect.x1, rect.y1, rect.x2, rect.y2);
    }

    return 0;
}

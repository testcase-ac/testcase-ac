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

Rect shrinkRect(const Rect& outer, int step) {
    return {outer.x1 + step, outer.y1 + step, outer.x2 - step, outer.y2 - step};
}

void addNestedChain(vector<Rect>& rects, Rect box, int depth) {
    for (int i = 0; i < depth; ++i) {
        rects.push_back(box);
        int room = min(box.x2 - box.x1, box.y2 - box.y1);
        if (room <= 8) {
            return;
        }
        int step = rnd.next(2, max(2, room / 4));
        box = shrinkRect(box, step);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Rect> rects;
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        int depth = rnd.next(2, 8);
        Rect box{rnd.next(0, 20), rnd.next(0, 20), rnd.next(120, 220), rnd.next(120, 220)};
        addNestedChain(rects, box, depth);
    } else if (mode == 1) {
        int rows = rnd.next(1, 3);
        int cols = rnd.next(2, 4);
        int baseX = rnd.next(0, 20);
        int baseY = rnd.next(0, 20);
        int cell = rnd.next(25, 45);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int x1 = baseX + c * cell + rnd.next(0, 3);
                int y1 = baseY + r * cell + rnd.next(0, 3);
                int w = rnd.next(6, cell - 8);
                int h = rnd.next(6, cell - 8);
                rects.push_back({x1, y1, x1 + w, y1 + h});
            }
        }
    } else if (mode == 2) {
        int groups = rnd.next(2, 4);
        for (int g = 0; g < groups; ++g) {
            int x = g * 90 + rnd.next(0, 10);
            int y = rnd.next(0, 25);
            Rect box{x, y, x + rnd.next(45, 70), y + rnd.next(45, 70)};
            addNestedChain(rects, box, rnd.next(1, 4));
        }
    } else {
        Rect outer{0, 0, rnd.next(180, 260), rnd.next(180, 260)};
        rects.push_back(outer);
        int count = rnd.next(3, 8);
        int slot = (outer.x2 - outer.x1 - 20) / count;
        for (int i = 0; i < count; ++i) {
            int x1 = 10 + i * slot + rnd.next(0, max(0, slot - 12));
            int y1 = rnd.next(10, outer.y2 - 35);
            int w = rnd.next(5, min(14, outer.x2 - x1 - 5));
            int h = rnd.next(5, min(20, outer.y2 - y1 - 5));
            rects.push_back({x1, y1, x1 + w, y1 + h});
        }
    }

    shuffle(rects.begin(), rects.end());

    println(static_cast<int>(rects.size()));
    for (const Rect& rect : rects) {
        println(rect.x1, rect.y1, rect.x2, rect.y2);
    }

    return 0;
}

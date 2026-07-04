#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
};

vector<int> buildLines(int count, int minGap, int maxGap) {
    vector<int> lines(count + 1);
    int cur = rnd.next(0, 20);
    lines[0] = cur;
    for (int i = 0; i < count; ++i) {
        cur += rnd.next(1, 8);
        lines[i + 1] = cur;
        if (i + 1 < count) {
            cur += rnd.next(minGap, maxGap);
        }
    }
    return lines;
}

void printRects(vector<Rect> rects) {
    shuffle(rects.begin(), rects.end());
    println((int)rects.size());
    for (const Rect& r : rects) {
        println(r.x1, r.y1, r.x2, r.y2);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<Rect> rects;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        vector<int> xs = buildLines(n, 1, 5);
        for (int i = 0; i < n; ++i) {
            int y1 = rnd.next(0, 80);
            int h = rnd.next(1, 10);
            rects.push_back({xs[i], y1, xs[i + 1], y1 + h});
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 14);
        int y1 = rnd.next(0, 30);
        int y2 = y1 + rnd.next(1, 10);
        int x = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 7);
            rects.push_back({x, y1, x + w, y2});
            x += w;
            if (rnd.next(0, 3) == 0) {
                x += rnd.next(1, 4);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 14);
        int x1 = rnd.next(0, 30);
        int x2 = x1 + rnd.next(1, 10);
        int y = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            int h = rnd.next(1, 7);
            rects.push_back({x1, y, x2, y + h});
            y += h;
            if (rnd.next(0, 3) == 0) {
                y += rnd.next(1, 4);
            }
        }
    } else {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 5);
        vector<int> xs = buildLines(cols, 0, mode == 3 ? 0 : 3);
        vector<int> ys = buildLines(rows, 0, mode == 3 ? 0 : 3);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (rnd.next(0, 99) < 70) {
                    rects.push_back({xs[c], ys[r], xs[c + 1], ys[r + 1]});
                }
            }
        }
        if (rects.empty()) {
            int r = rnd.next(0, rows - 1);
            int c = rnd.next(0, cols - 1);
            rects.push_back({xs[c], ys[r], xs[c + 1], ys[r + 1]});
        }
    }

    printRects(rects);
    return 0;
}

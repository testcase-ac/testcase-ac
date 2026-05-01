#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Rect { int x1, y1, x2, y2; };

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of rectangles
    int N = rnd.next(5, 10);
    // Arm length
    int R = rnd.next(3, 20);

    vector<Rect> rects;

    // 1) Rectangle containing the origin
    {
        int w = rnd.next(1, max(1, R/2));
        int h = rnd.next(1, max(1, R/2));
        rects.push_back({-w, -h, w, h});
    }
    // 2) Far away rectangle (never touches)
    {
        int x1 = R + rnd.next(1, 10);
        int y1 = R + rnd.next(1, 10);
        int w = rnd.next(1, 5);
        int h = rnd.next(1, 5);
        rects.push_back({x1, y1, x1 + w, y1 + h});
    }
    // 3) Rectangle touching at a corner exactly at distance R
    {
        int w = rnd.next(1, min(R, 5));
        int h = rnd.next(1, 5);
        // Make top-right corner at (R, 0)
        rects.push_back({R - w, -h, R, 0});
    }
    // 4) Rectangle touching at a side exactly at distance R
    {
        int w = rnd.next(1, R);
        int h = rnd.next(1, 5);
        // Bottom side at y = R
        rects.push_back({-w, R, w, R + h});
    }
    // Remaining random rectangles
    int rem = N - (int)rects.size();
    for (int i = 0; i < rem; i++) {
        int x1 = rnd.next(-R - 5, R + 5);
        int y1 = rnd.next(-R - 5, R + 5);
        int w = rnd.next(1, 6);
        int h = rnd.next(1, 6);
        rects.push_back({x1, y1, x1 + w, y1 + h});
    }

    // Shuffle for randomness
    shuffle(rects.begin(), rects.end());

    // Output
    println(N, R);
    for (auto &r : rects) {
        // Clockwise: bottom-left, bottom-right, top-right, top-left
        printf("%d %d %d %d %d %d %d %d\n",
               r.x1, r.y1,
               r.x2, r.y1,
               r.x2, r.y2,
               r.x1, r.y2);
    }
    return 0;
}

#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose world size from a small set for hand-checkable bounds
    vector<int> possibleBounds = {10, 20, 30, 50};
    int boundX = rnd.any(possibleBounds);
    int boundY = rnd.any(possibleBounds);

    // Number of rectangles
    int N = rnd.next(1, 10);
    println(N);

    // Hyper-parameters to control diversity
    double overlapProb = rnd.next();      // chance to overlap an existing rect
    double largeRectProb = rnd.next();    // chance to generate a "large" rectangle

    vector<array<int,4>> rects;
    rects.reserve(N);

    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        // With some probability, generate a rectangle overlapping a previous one
        if (i > 0 && rnd.next() < overlapProb) {
            auto r = rnd.any(rects);
            int w0 = r[2] - r[0];
            int h0 = r[3] - r[1];
            // choose a sub-rectangle inside the chosen one
            int w = rnd.next(1, w0);
            int h = rnd.next(1, h0);
            x1 = r[0] + rnd.next(0, w0 - w);
            y1 = r[1] + rnd.next(0, h0 - h);
            x2 = x1 + w;
            y2 = y1 + h;
        }
        else {
            // Sample a large or small rectangle
            bool isLarge = rnd.next() < largeRectProb;
            int maxW = isLarge ? boundX : max(1, boundX / 4);
            int maxH = isLarge ? boundY : max(1, boundY / 4);
            int w = rnd.next(1, maxW);
            int h = rnd.next(1, maxH);
            x1 = rnd.next(0, boundX - w);
            y1 = rnd.next(0, boundY - h);
            x2 = x1 + w;
            y2 = y1 + h;
        }
        rects.push_back({x1, y1, x2, y2});
        println(x1, y1, x2, y2);
    }

    return 0;
}

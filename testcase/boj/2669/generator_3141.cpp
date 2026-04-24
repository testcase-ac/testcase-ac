#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for bounding box size
    int W = rnd.next(1, 10);
    int H = rnd.next(1, 10);
    // Values for weighted randomness
    vector<int> tvals = {-2, -1, 0, 1, 2};

    // Generate four rectangles
    vector<array<int,4>> rects;
    for (int i = 0; i < 4; i++) {
        int t1 = rnd.any(tvals);
        int t2 = rnd.any(tvals);
        // width and height in [1..W] and [1..H] with skew
        int wi = rnd.wnext(W, t1) + 1;
        int hi = rnd.wnext(H, t2) + 1;
        // bottom-left corner
        int x1 = rnd.next(1, W + 1 - wi);
        int y1 = rnd.next(1, H + 1 - hi);
        int x2 = x1 + wi;
        int y2 = y1 + hi;
        rects.push_back({x1, y1, x2, y2});
    }

    // Shuffle output order for unpredictability
    shuffle(rects.begin(), rects.end());

    // Print four rectangles
    for (auto &r : rects) {
        println(r[0], r[1], r[2], r[3]);
    }
    return 0;
}

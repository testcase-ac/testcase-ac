#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions of the grid
    int M = rnd.next(5, 15); // height (y from 0 to M)
    int N = rnd.next(5, 15); // width  (x from 0 to N)
    // Number of rectangles
    int K = rnd.next(1, 3);
    // Pick a forced-uncovered cell
    int fx = rnd.next(0, N - 1);
    int fy = rnd.next(0, M - 1);

    vector<array<int,4>> rects;
    while ((int)rects.size() < K) {
        // Choose size category: small, medium, large
        int t = rnd.next(0, 2);
        int w, h;
        if (t == 0) {
            // small
            w = rnd.next(1, max(1, N / 4));
            h = rnd.next(1, max(1, M / 4));
        } else if (t == 1) {
            // medium
            w = rnd.next(max(1, N / 4), max(1, N / 2));
            h = rnd.next(max(1, M / 4), max(1, M / 2));
        } else {
            // large
            w = rnd.next(max(1, N / 2), N);
            h = rnd.next(max(1, M / 2), M);
        }
        // choose position
        int x1 = rnd.next(0, N - w);
        int y1 = rnd.next(0, M - h);
        int x2 = x1 + w;
        int y2 = y1 + h;
        // ensure forced cell (fx,fy) is not covered
        if (x1 <= fx && fx < x2 && y1 <= fy && fy < y2) {
            continue;
        }
        rects.push_back({x1, y1, x2, y2});
    }
    // Shuffle the rectangles for diversity
    shuffle(rects.begin(), rects.end());
    // Output
    println(M, N, K);
    for (auto &r : rects) {
        println(r[0], r[1], r[2], r[3]);
    }
    return 0;
}

#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of rectangles
    int N = rnd.next(3, 12);
    // Choose K with some bias to edges
    int K;
    double r = rnd.next();
    if (r < 0.2) {
        K = 1;
    } else if (r < 0.4) {
        K = N;
    } else if (N >= 3) {
        K = rnd.next(2, N - 1);
    } else {
        K = rnd.next(1, N);
    }
    // Generate rectangles with one of several patterns
    vector<array<int,4>> recs;
    int type = rnd.next(0, 3);
    if (type == 0) {
        // Fully random small rectangles
        for (int i = 0; i < N; i++) {
            int x1 = rnd.next(-100, 100);
            int y1 = rnd.next(-100, 100);
            int dx = rnd.next(1, 50);
            int dy = rnd.next(1, 50);
            recs.push_back({x1, y1, x1 + dx, y1 + dy});
        }
    } else if (type == 1) {
        // Nested rectangles
        int X1 = -1000, Y1 = -1000, X2 = 1000, Y2 = 1000;
        for (int i = 0; i < N; i++) {
            int mx = rnd.next(1, 10) * (i + 1);
            int my = rnd.next(1, 10) * (i + 1);
            recs.push_back({X1 + mx, Y1 + my, X2 - mx, Y2 - my});
        }
    } else if (type == 2) {
        // Vertical stripes
        int x = -500;
        for (int i = 0; i < N; i++) {
            int w = rnd.next(10, 50);
            int x1 = x;
            int x2 = x + w;
            int y1 = rnd.next(-1000, 0);
            int y2 = rnd.next(y1 + 1, 1000);
            recs.push_back({x1, y1, x2, y2});
            x = x2 + rnd.next(0, 20);
        }
    } else {
        // Horizontal stripes
        int y = -500;
        for (int i = 0; i < N; i++) {
            int h = rnd.next(10, 50);
            int y1 = y;
            int y2 = y + h;
            int x1 = rnd.next(-1000, 0);
            int x2 = rnd.next(x1 + 1, 1000);
            recs.push_back({x1, y1, x2, y2});
            y = y2 + rnd.next(0, 20);
        }
    }
    // Shuffle to randomize rectangle IDs (affects overlap priority)
    shuffle(recs.begin(), recs.end());
    // Output
    println(N, K);
    for (auto &rc : recs) {
        println(rc[0], rc[1], rc[2], rc[3]);
    }
    return 0;
}

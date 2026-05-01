#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with varied sizes
    int N;
    int tierN = rnd.next(0, 2);
    if (tierN == 0) N = rnd.next(1, 5);
    else if (tierN == 1) N = rnd.next(6, 15);
    else N = rnd.next(16, 30);
    // Choose region size in tenths for diversity: small, medium, large
    int thrX = rnd.next(0, 2), Rx;
    if (thrX == 0) Rx = rnd.next(10, 50);
    else if (thrX == 1) Rx = rnd.next(51, 200);
    else Rx = rnd.next(201, 10000);
    int thrY = rnd.next(0, 2), Ry;
    if (thrY == 0) Ry = rnd.next(10, 50);
    else if (thrY == 1) Ry = rnd.next(51, 200);
    else Ry = rnd.next(201, 10000);
    // Generate rectangles (x0,y0,w0,h0) in tenths
    vector<array<int,4>> rects;
    for (int i = 0; i < N; i++) {
        int w0 = rnd.next(1, Rx);
        int h0 = rnd.next(1, Ry);
        int x0 = rnd.next(0, Rx - w0);
        int y0 = rnd.next(0, Ry - h0);
        // Occasionally nest inside a previous rectangle
        if (i > 0 && rnd.next(0, 4) == 0) {
            int j = rnd.next(0, i - 1);
            auto pr = rects[j];
            w0 = rnd.next(1, pr[2]);
            h0 = rnd.next(1, pr[3]);
            int dx = pr[2] - w0;
            int dy = pr[3] - h0;
            x0 = pr[0] + rnd.next(0, dx);
            y0 = pr[1] + rnd.next(0, dy);
        }
        rects.push_back({x0, y0, w0, h0});
    }
    // Output
    println(N);
    for (auto &r : rects) {
        double x = r[0] / 10.0;
        double y = r[1] / 10.0;
        double w = r[2] / 10.0;
        double h = r[3] / 10.0;
        printf("%.1f %.1f %.1f %.1f\n", x, y, w, h);
    }
    return 0;
}

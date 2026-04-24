#include "testlib.h"
#include <vector>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of operations
    int L = rnd.next(5, 15);
    // Grid size parameters
    int MaxX = rnd.next(3, 10);
    // Maximum y-coordinate, biased towards smaller values
    int Ymax = rnd.wnext(50, -2) + 1;
    // Probability of a hit operation
    double hit_p = rnd.next(2, 8) / 10.0;

    vector<array<int,5>> ops;
    bool hasQuery = false;
    for (int i = 0; i < L; i++) {
        int t = (rnd.next() < hit_p ? 0 : 1);
        if (t == 0) {
            // Generate a hit rectangle
            int dxType = rnd.next(0, 2);
            int w;
            if (dxType == 0) w = 0;
            else if (dxType == 1) w = rnd.next(0, min(2, MaxX - 1));
            else w = rnd.next(0, MaxX - 1);

            int x1 = rnd.next(1, MaxX);
            int x2 = x1 + w;
            if (x2 > MaxX) x2 = rnd.next(1, MaxX);

            int dyType = rnd.next(0, 2);
            int h;
            if (dyType == 0) h = 0;
            else if (dyType == 1) h = rnd.next(0, min(3, Ymax - 1));
            else h = rnd.next(0, Ymax - 1);

            int y1 = rnd.next(1, Ymax);
            int y2 = y1 + h;
            if (y2 > Ymax) y2 = rnd.next(1, Ymax);

            ops.push_back({t, x1, y1, x2, y2});
        } else {
            // Generate a query
            hasQuery = true;
            int x1 = rnd.next(1, MaxX);
            int y1 = rnd.next(1, Ymax);
            int x2 = rnd.next(1, MaxX);
            int y2 = rnd.next(1, Ymax);
            ops.push_back({t, x1, y1, x2, y2});
        }
    }

    // Ensure at least one query
    if (!hasQuery) {
        ops.back() = {1,
            rnd.next(1, MaxX), rnd.next(1, Ymax),
            rnd.next(1, MaxX), rnd.next(1, Ymax)
        };
    }

    // Output
    println(L);
    for (auto &a : ops) {
        println(a[0], a[1], a[2], a[3], a[4]);
    }
    return 0;
}

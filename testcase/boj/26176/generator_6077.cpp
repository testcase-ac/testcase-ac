#include "testlib.h"
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

// compute number of whole 1x1 squares fully inside circle of radius R centered at origin
long long countSquares(int R) {
    long long cnt = 0;
    int lim = R; // bottom-left corner can be from -R to R-1
    long long R2 = 1LL * R * R;
    for (int x = -lim; x < lim; x++) {
        for (int y = -lim; y < lim; y++) {
            // check all four corners
            long long d1 = 1LL*(x)*(x) + 1LL*(y)*(y);
            long long d2 = 1LL*(x+1)*(x+1) + 1LL*(y)*(y);
            long long d3 = 1LL*(x)*(x) + 1LL*(y+1)*(y+1);
            long long d4 = 1LL*(x+1)*(x+1) + 1LL*(y+1)*(y+1);
            if (d1 <= R2 && d2 <= R2 && d3 <= R2 && d4 <= R2)
                cnt++;
        }
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a scenario for s
    // 0: minimal, 1: small random, 2: threshold around integer R, 3: medium, 4: large, 5: random mid-large
    int scenario = rnd.next(0,5);
    long long s = 1;
    if (scenario == 0) {
        // minimal edge
        s = 1;
    } else if (scenario == 1) {
        // small random
        s = rnd.next(1, 20);
    } else if (scenario == 2) {
        // near perfect square-count thresholds for integer radius
        int R = rnd.next(2, 20);
        long long base = countSquares(R);
        vector<long long> del = { -1, 0, 1 };
        long long d = rnd.any(del);
        s = base + d;
        if (s < 1) s = 1;
    } else if (scenario == 3) {
        // medium range
        s = rnd.next(50, 10000);
    } else if (scenario == 4) {
        // large near upper bound
        s = rnd.next(100000000, 1000000000);
    } else {
        // mid-large random
        s = rnd.next(10000, 500000000);
    }
    // Ensure within constraints
    if (s < 1) s = 1;
    if (s > 1000000000LL) s = 1000000000LL;
    println(s);
    return 0;
}

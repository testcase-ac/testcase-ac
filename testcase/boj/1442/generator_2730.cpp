#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose overall upper bound for R, keeping values small
    int sizeType = rnd.next(0, 2);
    int maxR;
    if (sizeType == 0) {
        // Very small range
        maxR = rnd.next(0, 20);
    } else if (sizeType == 1) {
        // Medium range
        maxR = rnd.next(21, 100);
    } else {
        // Larger but still hand-checkable
        maxR = rnd.next(101, 200);
    }

    // Initial random [L, R]
    int L = rnd.next(0, maxR);
    int R = rnd.next(L, maxR);

    // Boundary values around powers of two to catch tricky cases
    vector<int> boundaries = {7,8,15,16,31,32,63,64,127,128};
    vector<int> B;
    for (int b : boundaries) {
        if (b <= maxR) B.push_back(b);
    }

    // Sometimes align L or R (or both) to these boundaries
    int alignType = rnd.next(0, 3);
    if (!B.empty()) {
        if (alignType == 1) {
            // Align L to a boundary, then pick R >= L
            int x = rnd.any(B);
            L = x;
            R = rnd.next(L, maxR);
        } else if (alignType == 2) {
            // Align R to a boundary, then pick L <= R
            int x = rnd.any(B);
            R = x;
            L = rnd.next(0, R);
        } else if (alignType == 3) {
            // Align both L and R to two boundaries
            int x = rnd.any(B);
            int y = rnd.any(B);
            L = min(x, y);
            R = max(x, y);
        }
    }

    // Output a single test case: L R
    println(L, R);
    return 0;
}

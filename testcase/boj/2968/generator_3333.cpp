#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for maximum dimension (small for hand-checkable)
    int maxDim = 10;

    // Shape hyperparameter: sometimes square, sometimes rectangle
    bool squareShape = rnd.next(0, 1);
    int R, C;
    if (squareShape) {
        int s = rnd.next(1, maxDim);
        R = s; C = s;
    } else {
        R = rnd.next(1, maxDim);
        C = rnd.next(1, maxDim);
    }
    // Randomly swap to get R <-> C sometimes
    if (rnd.next(0, 1))
        swap(R, C);

    // Total cells (fits in int since maxDim is small)
    int total = R * C;

    // K hyperparameter: bias toward small, large, or uniform
    int K;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // small K (biased toward 1)
        K = rnd.wnext(total, -2) + 1;
    } else if (mode == 1) {
        // large K (biased toward total)
        int d = rnd.wnext(total, -2);
        K = total - d;
        if (K < 1) K = 1;
    } else {
        // uniform K
        K = rnd.next(1, total);
    }

    // Output in the required format
    println(R, C);
    println(K);

    return 0;
}

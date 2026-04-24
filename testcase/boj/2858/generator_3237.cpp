#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a shape type for diversity
    int shape = rnd.next(0, 2);
    int W, L;
    if (shape == 0) {
        // square-ish
        W = rnd.next(3, 20);
        int diff = rnd.next(0, 3);
        L = W + diff;
    } else if (shape == 1) {
        // elongated (L much larger than W)
        W = rnd.next(3, 8);
        L = rnd.next(W + 3, W * 5);
    } else {
        // small rectangle
        W = rnd.next(3, 10);
        L = rnd.next(W, W + 5);
    }

    if (L < W) swap(L, W);
    if (W < 3) W = 3;

    int R = 2 * L + 2 * W - 4;
    int B = L * W - R;

    // fallback to ensure valid
    if (B < 1) {
        L = 3; W = 3;
        R = 8; B = 1;
    }

    println(R, B);
    return 0;
}

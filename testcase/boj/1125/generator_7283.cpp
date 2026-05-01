#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MAX = 1000000;

    // Hyper-parameter for width W
    int W;
    if (rnd.next(0, 1) == 0) {
        // small width
        W = rnd.next(1, 20);
    } else {
        // random width up to MAX
        W = rnd.next(1, MAX);
    }
    // Occasionally force a specific remainder mod 5 to test boundary cuts
    if (rnd.next(0, 2) == 0) {
        int rem = rnd.next(1, 4);
        if (W <= rem) W = rem + rnd.next(1, 5);
        W = W - (W % 5) + rem;
        if (W > MAX) W = MAX - ((MAX - rem) % 5);
    }

    // Hyper-parameter for height H
    int H;
    if (rnd.next(0, 1) == 0) {
        // small height
        H = rnd.next(1, 20);
    } else {
        // random height up to MAX
        H = rnd.next(1, MAX);
    }
    // Occasionally enforce even/odd height
    if (rnd.next(0, 3) == 0) {
        if (rnd.next(0, 1) == 0) {
            // force even
            if (H % 2) H++;
            if (H > MAX) H--;
        } else {
            // force odd
            if ((H % 2) == 0) H++;
            if (H > MAX) H--;
        }
    }

    // Choose x1 and y1, sometimes edge-aligned
    int x1, y1;
    if (rnd.next(0, 9) == 0) x1 = 0;
    else x1 = rnd.next(0, MAX - W);
    if (rnd.next(0, 9) == 0) y1 = 0;
    else y1 = rnd.next(0, MAX - H);

    int x2 = x1 + W;
    int y2 = y1 + H;
    // Clamp to bounds
    if (x2 > MAX) { x2 = MAX; x1 = max(0, x2 - W); }
    if (y2 > MAX) { y2 = MAX; y1 = max(0, y2 - H); }
    // Ensure non-zero area
    if (x1 == x2) x2 = x1 + 1;
    if (y1 == y2) y2 = y1 + 1;

    println(x1, y1, x2, y2);
    return 0;
}

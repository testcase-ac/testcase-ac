#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for R: choose among very small to very large
    int R;
    int rtype = rnd.next(0, 4);
    if (rtype == 0) {
        R = rnd.next(2, 10);
    } else if (rtype == 1) {
        R = rnd.next(11, 100);
    } else if (rtype == 2) {
        R = rnd.next(101, 1000);
    } else if (rtype == 3) {
        R = rnd.next(1001, 10000);
    } else {
        R = rnd.next(10001, 100000);
    }

    // Hyper-parameter for r: minimal, maximal, or random
    int r;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // minimal possible
        r = 1;
    } else if (mode == 1) {
        // maximal possible under 2*r <= R
        r = R / 2;
    } else {
        // random in [1, R/2]
        r = rnd.next(1, R / 2);
    }

    // Output R and r
    println(R, r);
    return 0;
}

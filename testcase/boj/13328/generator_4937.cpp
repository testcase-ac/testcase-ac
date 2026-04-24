#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for d
    int d = rnd.next(2, 50);

    // Hyper-parameter for t: small & diverse relative to d
    int t;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Very small time
        t = 1;
    } else if (mode == 1) {
        // t in [1, min(d,20)]
        t = rnd.next(1, min(d, 20));
    } else {
        // t just above d, but capped at 20
        int lo = d + 1;
        int hi = min(d + 5, 20);
        if (lo <= hi) t = rnd.next(lo, hi);
        else t = rnd.next(1, 20);
    }

    // Output the single test case
    println(d, t);
    return 0;
}

#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for bottle height h
    int hType = rnd.next(0, 2);
    int h;
    if (hType == 0)       h = rnd.next(1, 10);
    else if (hType == 1)  h = rnd.next(10, 100);
    else                  h = rnd.next(100, 1000);
    // Hyper-parameter for bottle radius r
    int rType = rnd.next(0, 2);
    int r;
    if (rType == 0)       r = rnd.next(1, 10);
    else if (rType == 1)  r = rnd.next(1, 100);
    else                  r = rnd.next(1, 1000);
    // Hyper-parameter for densities: sometimes small difference, sometimes arbitrary
    bool smallDiff = rnd.next(0, 1) == 0;
    int d_a, d_w;
    if (smallDiff) {
        // small difference between d_w and d_a
        d_a = rnd.next(1, 995);
        int maxDelta = min(5, 1000 - d_a);
        d_w = d_a + rnd.next(1, maxDelta);
    } else {
        // general random densities with d_a < d_w
        d_a = rnd.next(1, 999);
        d_w = rnd.next(d_a + 1, 1000);
    }
    // Output one test case
    println(h, r, d_a, d_w);
    return 0;
}

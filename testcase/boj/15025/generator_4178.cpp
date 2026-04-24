#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We will generate three types of cases:
    // 1) Not a moose: both sides zero (≈10%)
    // 2) Even-pointed moose: l == r > 0 (≈30%)
    // 3) Odd-pointed moose: l != r (≈60%)
    double p = rnd.next();
    int l, r;
    if (p < 0.1) {
        // Not a moose
        l = r = 0;
    } else if (p < 0.4) {
        // Even-pointed, choose k from 1 to 20
        int k = rnd.next(1, 20);
        l = r = k;
    } else {
        // Odd-pointed, choose max tines and smaller side
        int mx = rnd.next(1, 20);
        int mn = rnd.next(0, mx - 1);
        // Randomly assign which side gets the max
        if (rnd.next(0,1) == 0) {
            l = mx; r = mn;
        } else {
            l = mn; r = mx;
        }
    }

    // Output the single test case
    println(l, r);

    return 0;
}

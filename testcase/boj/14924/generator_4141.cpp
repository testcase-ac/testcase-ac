#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for train speed S: small, medium, or large
    int sType = rnd.next(0, 2);
    int S_low, S_high;
    if (sType == 0) {
        S_low = 1; S_high = 10;
    } else if (sType == 1) {
        S_low = 11; S_high = 1000;
    } else {
        S_low = 1001; S_high = 5000;
    }
    int S = rnd.next(S_low, S_high);

    // Hyper-parameter for fly speed T: choose a delta above S
    int maxDelta = 10000 - S;
    int tType = rnd.next(0, 2);
    int d_low, d_high;
    if (tType == 0) {
        d_low = 1; d_high = min(10, maxDelta);
    } else if (tType == 1) {
        d_low = 11; d_high = min(1000, maxDelta);
    } else {
        d_low = 1001; d_high = maxDelta;
    }
    if (d_low > d_high) {
        d_low = 1; d_high = maxDelta;
    }
    int delta = rnd.next(d_low, d_high);
    int T = S + delta;

    // Hyper-parameter for distance D: must be multiple of 2*S and ≤10000
    int kmax = 10000 / (2 * S);
    int k_low, k_high;
    if (kmax >= 6) {
        if (rnd.next(0, 1) == 0) {
            k_low = 1; k_high = min(5, kmax);
        } else {
            k_low = 6; k_high = kmax;
        }
    } else {
        k_low = 1; k_high = kmax;
    }
    int k = rnd.next(k_low, k_high);
    int D = 2 * S * k;

    // Output the test case
    println(S, T, D);
    return 0;
}

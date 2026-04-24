#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A, B, C, I, J, K;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // small values
        A = rnd.next(1, 5);
        B = rnd.next(1, 5);
        C = rnd.next(1, 5);
        I = rnd.next(1, 5);
        J = rnd.next(1, 5);
        K = rnd.next(1, 5);
    } else if (mode == 1) {
        // trivial ratio 1:1:1
        A = rnd.next(1, 500);
        B = rnd.next(1, 500);
        C = rnd.next(1, 500);
        I = J = K = 1;
    } else if (mode == 2) {
        // balanced ratios close to each other
        int base = rnd.next(1, 50);
        int dj_lo = -min(base - 1, 5), dj_hi = min(50 - base, 5);
        int dk_lo = -min(base - 1, 5), dk_hi = min(50 - base, 5);
        I = base;
        J = base + rnd.next(dj_lo, dj_hi);
        K = base + rnd.next(dk_lo, dk_hi);
        A = rnd.next(1, 500);
        B = rnd.next(1, 500);
        C = rnd.next(1, 500);
    } else if (mode == 3) {
        // skewed: one large, two small
        A = rnd.next(1, 500);
        B = rnd.next(1, 500);
        C = rnd.next(1, 500);
        vector<int> r(3);
        r[0] = rnd.next(30, 50);
        r[1] = rnd.next(1, 10);
        r[2] = rnd.next(1, 10);
        shuffle(r.begin(), r.end());
        I = r[0];
        J = r[1];
        K = r[2];
    } else {
        // fully random
        A = rnd.next(1, 500);
        B = rnd.next(1, 500);
        C = rnd.next(1, 500);
        I = rnd.next(1, 50);
        J = rnd.next(1, 50);
        K = rnd.next(1, 50);
    }

    println(A, B, C);
    println(I, J, K);
    return 0;
}

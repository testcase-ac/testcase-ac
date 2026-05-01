#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXN = 500000;

    vector<int> special = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        16, 17, 18, 19, 20,
        50, 51, 52,
        100, 101, 102,
        256, 257,
        512, 513,
        1000, 1001,
        9999, 10000,
        12345,
        32768, 32769,
        65535, 65536,
        100000, 100001,
        131072, 131073,
        262143, 262144,
        353535,
        400000, 450000,
        499998, 499999, 500000
    };

    int n;
    int mode = rnd.next(1, 100);

    if (mode <= 45) {
        // Use one of the hand-picked special values
        n = rnd.any(special);
    } else if (mode <= 70) {
        // Very small n, easy to brute-force/check
        int hi = rnd.next(5, 20);
        n = rnd.next(1, hi);
    } else if (mode <= 85) {
        // Small/medium n
        int hi = rnd.next(50, 1000);
        n = rnd.next(1, hi);
    } else if (mode <= 95) {
        // Medium/large range, slightly biased towards larger values
        int hi = rnd.next(1000, MAXN);
        int t = rnd.next(1, 5);
        // wnext with positive t biases towards larger numbers
        n = rnd.wnext(hi, t) + 1; // wnext returns [0, hi-1]
    } else {
        // Pure large random, close to upper bound
        int lo = rnd.next(100000, 300000);
        int hi = MAXN;
        n = rnd.next(lo, hi);
    }

    println(n);
    return 0;
}

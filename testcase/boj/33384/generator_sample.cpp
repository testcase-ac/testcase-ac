#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {
        3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
    };
    const vector<int> mediumPrimes = {
        97, 101, 127, 251, 509, 997, 1009, 8191, 65537
    };
    const vector<int> largePrimes = {
        99991, 1000003, 10000019, 100000007, 999999937
    };

    int mode = rnd.next(0, 5);
    int p;
    int k;
    int t;

    if (mode == 0) {
        p = 3;
        k = rnd.next(1, 2);
        t = 1;
    } else if (mode == 1) {
        p = rnd.any(smallPrimes);
        k = rnd.next(1, p - 1);
        t = rnd.next(1, p - 2);
    } else if (mode == 2) {
        p = rnd.any(smallPrimes);
        k = rnd.next(0, 1) == 0 ? 1 : p - 1;
        t = rnd.next(1, p - 2);
    } else if (mode == 3) {
        p = rnd.any(mediumPrimes);
        k = rnd.next(1, p - 1);
        t = rnd.next(0, 1) == 0 ? 1 : p - 2;
    } else if (mode == 4) {
        p = rnd.any(mediumPrimes);
        k = rnd.next(1, p - 1);
        int lo = max(1, p / 2 - 10);
        int hi = min(p - 2, p / 2 + 10);
        t = rnd.next(lo, hi);
    } else {
        p = rnd.any(largePrimes);
        k = rnd.next(1, p - 1);
        vector<int> candidates = {1, 2, 3, p - 4, p - 3, p - 2};
        t = rnd.any(candidates);
    }

    println(p, k, t);
    return 0;
}

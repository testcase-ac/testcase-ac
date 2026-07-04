#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
    };
    const vector<int> largePrimes = {
        97, 101, 997, 1009, 10007, 99991, 999983, 9999991
    };

    int mode = rnd.next(0, 5);
    long long n;
    int p;
    int r;

    if (mode == 0) {
        p = rnd.any(smallPrimes);
        n = rnd.next(2LL, min(30LL, 2LL * p + 5));
        r = rnd.next(0, p - 1);
    } else if (mode == 1) {
        p = rnd.any(smallPrimes);
        n = rnd.next(2LL, max(2LL, 1LL * p - 1));
        r = rnd.next(0, p - 1);
    } else if (mode == 2) {
        p = rnd.any(smallPrimes);
        n = rnd.next(1LL * p, max(1LL * p, 2LL * p - 1));
        r = rnd.next(0, p - 1);
    } else if (mode == 3) {
        p = rnd.any(largePrimes);
        n = rnd.next(2LL, min(1000000000000000000LL, 2LL * p + 1000));
        r = rnd.next(0, p - 1);
    } else if (mode == 4) {
        p = rnd.any(largePrimes);
        n = rnd.next(1000000000000LL, 1000000000000000000LL);
        r = rnd.next(0, p - 1);
    } else {
        p = rnd.any(smallPrimes);
        vector<int> boundaryR = {0, 1, p - 1};
        n = rnd.any(vector<long long>{2LL, 1LL * p, 2LL * p, 1000000000000000000LL});
        r = rnd.any(boundaryR);
    }

    println(n, p, r);
    return 0;
}

#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {3, 5, 7, 11, 47, 101, 997};
    const vector<int> largePrimes = {99991, 100003, 500009, 999983};

    int mode = rnd.next(0, 5);
    int n = 0;
    int m = 0;
    long long k = 1;
    int p = rnd.any(smallPrimes);

    if (mode == 0) {
        n = rnd.next(0, 8);
        m = rnd.next(0, 8);
        k = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(0, 1) == 0 ? 0 : rnd.next(1, 20);
        m = n == 0 ? rnd.next(1, 30) : 0;
        k = rnd.next(1, 80);
        if (m > 0 && rnd.next(0, 1) == 0 && k % 2 == 1) {
            ++k;
        }
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        m = rnd.next(1, 30);
        k = rnd.next(1, 200);
        if (rnd.next(0, 1) == 0) {
            k = 2LL * rnd.next(1, 100);
        }
    } else if (mode == 3) {
        n = rnd.next(250, 300);
        m = rnd.next(250, 300);
        k = rnd.next(1, 1000000);
        p = rnd.any(largePrimes);
    } else if (mode == 4) {
        n = rnd.next(0, 300);
        m = rnd.next(0, 300);
        k = rnd.next(999999000000LL, 1000000000000LL);
        p = rnd.any(largePrimes);
    } else {
        n = rnd.next(0, 300);
        m = rnd.next(0, 300);
        k = rnd.next(1LL, 1000000000000LL);
        p = rnd.any(rnd.next(0, 1) == 0 ? smallPrimes : largePrimes);
    }

    println(n, m, k, p);
    return 0;
}

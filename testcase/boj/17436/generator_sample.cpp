#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> allPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                             31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                             73, 79, 83, 89, 97};

    int mode = rnd.next(0, 5);
    int n;
    long long m;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 250);
    } else if (mode == 1) {
        n = rnd.next(4, 7);
        m = rnd.next(50, 10000);
    } else if (mode == 2) {
        n = rnd.next(8, 10);
        m = rnd.next(1000, 1000000);
    } else if (mode == 3) {
        n = rnd.next(1, 10);
        m = rnd.next(999999999000LL, 1000000000000LL);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        int anchor = rnd.any(allPrimes);
        long long q = rnd.next(1LL, 1000000000000LL / anchor);
        m = anchor * q + rnd.next(-1, 1);
        m = max(1LL, min(1000000000000LL, m));
    } else {
        n = 10;
        m = 1000000000000LL;
    }

    if (mode <= 2) {
        int span = rnd.next(n, min<int>(25, n + 8));
        vector<int> pool(allPrimes.begin(), allPrimes.begin() + span);
        shuffle(pool.begin(), pool.end());
        pool.resize(n);
        allPrimes = pool;
    } else {
        shuffle(allPrimes.begin(), allPrimes.end());
        allPrimes.resize(n);
    }

    if (rnd.next(0, 1)) {
        sort(allPrimes.begin(), allPrimes.end());
    }

    println(n, m);
    println(allPrimes);
    return 0;
}

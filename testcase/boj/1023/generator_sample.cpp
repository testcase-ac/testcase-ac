#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long maxKFor(int n) {
    return (1LL << n) - 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long maxK;
    long long k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        maxK = maxKFor(n);
        k = rnd.next(0LL, maxK);
    } else if (mode == 1) {
        vector<int> lengths = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 49, 50};
        n = rnd.any(lengths);
        maxK = maxKFor(n);

        vector<long long> candidates = {0, 1, 2, maxK / 2, maxK - 2, maxK - 1, maxK};
        vector<long long> valid;
        for (long long value : candidates) {
            if (0 <= value && value <= maxK) {
                valid.push_back(value);
            }
        }
        k = rnd.any(valid);
    } else if (mode == 2) {
        n = rnd.next(2, 16);
        maxK = maxKFor(n);
        long long window = min<long long>(maxK, rnd.next(0LL, 32LL));
        k = rnd.next(0, 1) == 0 ? window : maxK - window;
    } else if (mode == 3) {
        n = rnd.next(17, 50);
        maxK = maxKFor(n);
        k = rnd.next(0LL, maxK);
    } else if (mode == 4) {
        n = rnd.next(1, 50);
        if (rnd.next(0, 1) == 0 && n > 1) {
            --n;
        }
        maxK = maxKFor(n);
        int bit = rnd.next(0, n - 1);
        k = 1LL << bit;
        if (rnd.next(0, 1) == 0 && k > 0) {
            --k;
        }
    } else {
        n = rnd.next(1, 50);
        maxK = maxKFor(n);
        k = rnd.wnext(maxK + 1, rnd.next(-3, 3));
    }

    println(n, k);
    return 0;
}

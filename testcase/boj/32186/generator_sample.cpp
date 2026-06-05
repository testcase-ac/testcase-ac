#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_A = 1000000000LL;

long long randomValueWithRoom(long long diff) {
    return rnd.next(1LL, MAX_A - diff);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 15);
    if (mode == 0) n = rnd.next(1, 3);
    if (mode == 5) n = rnd.next(10, 30);

    long long k;
    if (mode == 1) {
        k = 1;
    } else if (mode == 2) {
        k = rnd.next(500000000LL, 1000000000LL);
    } else {
        vector<long long> candidates = {2, 3, 4, 5, 7, 10, 97, 1000000000LL};
        k = rnd.next(0, 3) == 0 ? rnd.any(candidates) : rnd.next(2LL, 1000000LL);
    }

    vector<long long> a(n);
    for (int i = 0; i < (n + 1) / 2; ++i) {
        int j = n - 1 - i;
        long long diff = 0;

        if (i != j && mode != 3) {
            if (mode == 1) {
                diff = rnd.next(0LL, min(200LL, MAX_A - 1));
            } else if (mode == 2) {
                diff = rnd.next(0, 1) ? rnd.next(1LL, min(k - 1, MAX_A - 1)) : k;
            } else if (mode == 4) {
                long long q = rnd.next(0LL, min(20LL, (MAX_A - 1) / k));
                long long r = rnd.next(0, 1) ? rnd.next(0LL, min(k / 2, MAX_A - 1)) : max(0LL, k - rnd.next(0LL, min(3LL, k - 1)));
                diff = min(MAX_A - 1, q * k + r);
            } else {
                long long maxQ = min(25LL, (MAX_A - 1) / k);
                diff = rnd.next(0LL, maxQ) * k;
                if (rnd.next(0, 1) && diff + 1 <= MAX_A - 1) diff += rnd.next(1LL, min(k - 1, MAX_A - 1 - diff));
            }
        }

        long long lo = randomValueWithRoom(diff);
        long long hi = lo + diff;
        if (rnd.next(0, 1)) swap(lo, hi);
        a[i] = lo;
        a[j] = hi;
    }

    println(n, k);
    println(a);

    return 0;
}

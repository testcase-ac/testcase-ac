#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000LL;
    const int MAX_K = 90;

    int mode = rnd.next(0, 8);
    long long n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 25);
        k = rnd.next(1, (int)min<long long>(MAX_K, n));
    } else if (mode == 1) {
        n = rnd.next(1, 200);
        k = 1;
    } else if (mode == 2) {
        k = rnd.next(2, MAX_K);
        n = rnd.next(k, k + rnd.next(0, 200));
    } else if (mode == 3) {
        k = rnd.next(2, MAX_K);
        long long q = rnd.next(1, 200);
        long long r = rnd.next(0, k - 1);
        n = q * k + r;
    } else if (mode == 4) {
        k = rnd.next(2, MAX_K);
        long long p = 1;
        int exponent = rnd.next(0, 49);
        for (int i = 0; i < exponent && p <= MAX_N / 2; ++i) {
            p *= 2;
        }
        n = max<long long>(k, p + rnd.next(-min<long long>(p - 1, 200), 200LL));
    } else if (mode == 5) {
        k = rnd.next(2, MAX_K);
        n = MAX_N - rnd.next(0LL, 1000000LL);
    } else if (mode == 6) {
        k = rnd.next(2, MAX_K);
        n = rnd.next(1LL, 1000000000LL);
        if (n < k) {
            n = k;
        }
    } else if (mode == 7) {
        vector<int> ks = {2, 3, 4, 5, 10, 30, 60, 89, 90};
        k = rnd.any(ks);
        n = rnd.next((long long)k, 1000000LL);
    } else {
        k = rnd.next(1, MAX_K);
        n = rnd.next((long long)k, MAX_N);
    }

    println(n, k);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000LL;
    long long n = 1;
    int mode = rnd.next(9);

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        n = rnd.next(1LL, LIMIT);
    } else if (mode == 2) {
        long long k = rnd.next(1LL, 1000000LL);
        n = k * k;
    } else if (mode == 3) {
        long long k = rnd.next(2LL, 1000000LL);
        long long delta = rnd.any(vector<long long>{-2, -1, 1, 2, 3, 5, 10});
        n = k * k + delta;
        n = max(1LL, min(LIMIT, n));
    } else if (mode == 4) {
        long long a = rnd.next(1LL, 700000LL);
        long long b = rnd.next(1LL, 700000LL);
        n = a * a + b * b;
    } else if (mode == 5) {
        vector<long long> factors = {2, 3, 5, 7, 11, 13, 17, 19};
        shuffle(factors.begin(), factors.end());
        n = 1;
        for (long long f : factors) {
            int repeats = rnd.next(0, 4);
            for (int i = 0; i < repeats && n <= LIMIT / f; ++i) n *= f;
        }
        if (n == 1) n = rnd.next(2LL, 1000LL);
    } else if (mode == 6) {
        long long base = rnd.next(2LL, 1000LL);
        n = 1;
        while (n <= LIMIT / base && rnd.next(2) == 1) n *= base;
        if (n == 1) n = base;
    } else if (mode == 7) {
        n = LIMIT - rnd.next(0LL, 10000LL);
    } else {
        long long a = rnd.next(1LL, 1000000LL);
        long long b = rnd.next(1LL, 1000000LL);
        n = max(1LL, min(LIMIT, a * b + rnd.next(0LL, 20LL)));
    }

    println(n);
    return 0;
}

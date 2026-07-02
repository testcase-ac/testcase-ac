#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 8589934591LL;
    long long n;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.next(1LL, 20LL);
    } else if (mode == 1) {
        long long half = rnd.next(1LL, 1000000LL);
        n = 2 * half + rnd.next(0LL, 1LL);
    } else if (mode == 2) {
        vector<long long> pivots;
        for (int bit = 0; bit <= 33; ++bit) {
            long long value = 1LL << bit;
            for (long long delta = -2; delta <= 2; ++delta) {
                long long candidate = value + delta;
                if (1 <= candidate && candidate <= MAX_N) {
                    pivots.push_back(candidate);
                }
            }
        }
        n = rnd.any(pivots);
    } else if (mode == 3) {
        long long base = rnd.next(1LL, 50000LL);
        n = min(MAX_N, base * base + rnd.next(0LL, base));
    } else if (mode == 4) {
        n = rnd.next(1LL, MAX_N);
    } else {
        n = MAX_N - rnd.next(0LL, 1000LL);
    }

    println(n);
    return 0;
}

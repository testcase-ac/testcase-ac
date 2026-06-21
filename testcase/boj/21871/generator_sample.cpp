#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;
    long long n = 1;
    long long k = 1;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        n = rnd.next(1LL, 5LL);
        k = rnd.next(1LL, 10LL);
    } else if (mode == 1) {
        n = rnd.next(1LL, 30LL);
        long long center = 2 * n;
        long long lo = max(1LL, center - 3);
        long long hi = min(LIM, center + 3);
        k = rnd.next(lo, hi);
    } else if (mode == 2) {
        n = rnd.next(1LL, 100LL);
        k = rnd.next(1LL, min(LIM, 2 * n));
        if (rnd.next(0, 1) == 0 && k < LIM) ++k;
        if (k % 2 == 1 && k > 1) --k;
    } else if (mode == 3) {
        n = rnd.next(1LL, 100LL);
        k = rnd.next(1LL, min(LIM, 2 * n));
        if (k % 2 == 0) {
            if (k < min(LIM, 2 * n)) ++k;
            else --k;
        }
    } else if (mode == 4) {
        n = rnd.next(1LL, 100000LL);
        k = rnd.next(min(LIM, 2 * n + 1), LIM);
    } else if (mode == 5) {
        n = rnd.next(LIM - 1000, LIM);
        k = rnd.next(1LL, LIM);
    } else if (mode == 6) {
        vector<pair<long long, long long>> cases = {
            {1, 1},
            {1, 2},
            {1, 3},
            {2, 4},
            {2, 5},
            {LIM, LIM},
        };
        auto chosen = rnd.any(cases);
        n = chosen.first;
        k = chosen.second;
    } else {
        n = rnd.next(1LL, LIM);
        long long span = rnd.next(1LL, 1000LL);
        long long base = min(LIM, 2 * n);
        long long lo = max(1LL, base - span);
        long long hi = min(LIM, base + span);
        k = rnd.next(lo, hi);
    }

    println(n, k);
    return 0;
}

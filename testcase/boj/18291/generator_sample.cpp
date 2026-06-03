#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000LL;
    int mode = rnd.next(0, 5);
    int t = rnd.next(1, mode == 5 ? 100 : 30);

    vector<long long> candidates = {
        1, 2, 3, 4, 5, 6, 7, 8,
        31, 32, 33, 63, 64, 65,
        999999937LL, 999999999LL, MAX_N,
        MAX_N - 3, MAX_N - 2, MAX_N - 1, MAX_N
    };

    for (int bit = 1; bit <= 29; ++bit) {
        long long base = 1LL << bit;
        for (long long delta = -2; delta <= 2; ++delta) {
            long long value = base + delta;
            if (1 <= value && value <= MAX_N) candidates.push_back(value);
        }
    }

    vector<long long> values;
    values.reserve(t);
    while ((int)values.size() < t) {
        long long n;
        if (mode == 0) {
            n = rnd.next(1, 12);
        } else if (mode == 1) {
            n = rnd.any(candidates);
        } else if (mode == 2) {
            long long hi = rnd.next(20, 1000000);
            n = rnd.next(1LL, hi);
        } else if (mode == 3) {
            n = MAX_N - rnd.next(0LL, 1000LL);
        } else if (mode == 4) {
            long long base = 1LL << rnd.next(1, 29);
            n = base + rnd.next(-10LL, 10LL);
            n = max(1LL, min(MAX_N, n));
        } else {
            n = rnd.next(1LL, MAX_N);
        }
        values.push_back(n);
    }

    if (rnd.next(0, 3) == 0) shuffle(values.begin(), values.end());

    println(t);
    for (long long n : values) println(n);

    return 0;
}

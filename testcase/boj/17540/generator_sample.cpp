#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_N = 2;
    const long long MAX_N = 1000000000000000000LL;

    vector<long long> candidates;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        candidates = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 16};
    } else if (mode == 1) {
        int bit = rnd.next(1, 59);
        long long base = 1LL << bit;
        for (long long delta = -3; delta <= 3; ++delta) {
            long long value = base + delta;
            if (MIN_N <= value && value <= MAX_N) candidates.push_back(value);
        }
    } else if (mode == 2) {
        int bits = rnd.next(2, 59);
        long long value = 0;
        for (int bit = 0; bit < bits; ++bit) {
            if (rnd.next(0, 1)) value |= 1LL << bit;
        }
        value |= 1LL << (bits - 1);
        candidates.push_back(max(MIN_N, value));
    } else if (mode == 3) {
        long long hi = rnd.any(vector<long long>{100, 10000, 1000000, 1000000000LL});
        candidates.push_back(rnd.next(MIN_N, hi));
    } else if (mode == 4) {
        long long tail = rnd.next(0LL, 1000000LL);
        candidates.push_back(MAX_N - tail);
    } else {
        candidates.push_back(rnd.next(MIN_N, MAX_N));
    }

    long long n = rnd.any(candidates);
    println(n);
    return 0;
}

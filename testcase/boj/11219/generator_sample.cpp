#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 100000000000LL;
    vector<long long> candidates;

    candidates.push_back(1);
    candidates.push_back(2);
    candidates.push_back(3);
    candidates.push_back(LIMIT);

    for (long long p = 1; p <= LIMIT; p *= 2) {
        for (long long delta = -3; delta <= 3; ++delta) {
            long long value = p + delta;
            if (1 <= value && value <= LIMIT) {
                candidates.push_back(value);
            }
        }
        if (p > LIMIT / 2) {
            break;
        }
    }

    int mode = rnd.next(0, 4);
    long long n;
    if (mode == 0) {
        n = rnd.any(candidates);
    } else if (mode == 1) {
        n = rnd.next(1LL, 1000LL);
    } else if (mode == 2) {
        long long high = rnd.next(max(1LL, LIMIT - 1000000LL), LIMIT);
        n = high;
    } else {
        long long bits = rnd.next(1LL, (1LL << rnd.next(1, 37)) - 1);
        n = min(bits, LIMIT);
    }

    println(n);
    return 0;
}

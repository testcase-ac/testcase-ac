#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_N = 1000000000000000000LL;

long long clampN(long long x) {
    return max(1LL, min(MAX_N, x));
}

long long pow2(int bit) {
    return 1LL << bit;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> candidates;
    candidates.push_back(1);
    candidates.push_back(2);
    candidates.push_back(3);
    candidates.push_back(7);
    candidates.push_back(MAX_N);

    int bit = rnd.next(1, 59);
    long long p = pow2(bit);
    candidates.push_back(clampN(p));
    candidates.push_back(clampN(p - 1));
    candidates.push_back(clampN(p + 1));

    long long mask = (1LL << rnd.next(1, 60)) - 1;
    candidates.push_back(clampN(mask));
    candidates.push_back(clampN(mask - rnd.next(0LL, min(1000LL, mask - 1))));

    long long high = rnd.next(1LL, MAX_N);
    long long lowBits = (1LL << rnd.next(0, 20)) - 1;
    candidates.push_back(clampN(high ^ lowBits));

    long long n;
    int mode = rnd.next(0, 5);
    if (mode <= 3) {
        n = rnd.any(candidates);
    } else if (mode == 4) {
        n = rnd.next(1LL, min(MAX_N, 1000000LL));
    } else {
        n = rnd.next(1LL, MAX_N);
    }

    println(n);
    return 0;
}

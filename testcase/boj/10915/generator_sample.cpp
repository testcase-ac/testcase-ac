#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMinN = 3;
    const long long kMaxN = 1000000000000LL;

    vector<long long> candidates = {
        kMinN,
        kMinN + 1,
        kMinN + 2,
        9,
        10,
        11,
        999999999999LL,
        kMaxN,
    };

    long long n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.any(candidates);
    } else if (mode == 1) {
        n = rnd.next(kMinN, 200LL);
    } else if (mode == 2) {
        n = rnd.next(1LL, 1000000LL) * rnd.next(1LL, 1000000LL);
        n = max(kMinN, min(kMaxN, n));
    } else if (mode == 3) {
        long long base = 1LL << rnd.next(2, 39);
        long long delta = rnd.next(-3LL, 3LL);
        n = max(kMinN, min(kMaxN, base + delta));
    } else if (mode == 4) {
        n = rnd.next(kMinN, kMaxN);
        if (n % 2 != 0) ++n;
        if (n > kMaxN) n -= 2;
    } else {
        n = rnd.next(kMinN, kMaxN);
        if (n % 2 == 0) ++n;
        if (n > kMaxN) n -= 2;
    }

    println(n);
    return 0;
}

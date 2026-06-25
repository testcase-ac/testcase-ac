#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

const ll LIMIT = 1000000000000000000LL;

ll clampRange(ll value) {
    return max(1LL, min(LIMIT, value));
}

ll pow2Value(int exponent) {
    return 1LL << exponent;
}

ll allOnesValue(int bits) {
    return (1LL << bits) - 1;
}

ll randomValue() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return rnd.next(1LL, 200LL);
    if (mode == 1) return rnd.next(1LL, 1000000LL);
    if (mode == 2) return rnd.next(LIMIT - 1000000LL, LIMIT);
    if (mode == 3) return clampRange(pow2Value(rnd.next(0, 59)) + rnd.next(-20LL, 20LL));
    if (mode == 4) return clampRange(allOnesValue(rnd.next(1, 59)) + rnd.next(-20LL, 20LL));
    return rnd.next(1LL, LIMIT);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(8, 24);
    vector<int> modes;
    for (int i = 0; i < cases; ++i) modes.push_back(i < 6 ? i : rnd.next(0, 5));
    shuffle(modes.begin(), modes.end());

    for (int mode : modes) {
        ll lo = 1;
        ll hi = 1;
        int x = rnd.next(0, 10);

        if (mode == 0) {
            lo = hi = randomValue();
        } else if (mode == 1) {
            ll center = pow2Value(rnd.next(0, 59));
            ll radius = rnd.next(0LL, 30LL);
            lo = clampRange(center - radius);
            hi = clampRange(center + radius);
            x = rnd.next(0, 4);
        } else if (mode == 2) {
            ll center = allOnesValue(rnd.next(1, 59));
            ll radius = rnd.next(0LL, 30LL);
            lo = clampRange(center - radius);
            hi = clampRange(center + radius);
            x = rnd.next(1, 5);
        } else if (mode == 3) {
            lo = rnd.next(1LL, LIMIT - 1000LL);
            hi = lo + rnd.next(0LL, 1000LL);
        } else if (mode == 4) {
            ll width = rnd.next(0LL, 1000000LL);
            hi = LIMIT - rnd.next(0LL, 1000LL);
            lo = max(1LL, hi - width);
            x = rnd.any(vector<int>{0, 1, 2, 3, 10});
        } else {
            lo = randomValue();
            ll width = rnd.next(0LL, 1000000000000LL);
            hi = min(LIMIT, lo + width);
            x = rnd.next(0, 10);
        }

        if (lo > hi) swap(lo, hi);
        println(lo, hi, x);
    }

    println(0, 0, 0);
    return 0;
}

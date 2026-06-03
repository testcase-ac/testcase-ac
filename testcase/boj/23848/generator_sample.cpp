#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;
using i128 = __int128_t;

const int64 LIMIT = 1000000000000LL;

int64 geometricFactor(int64 ratio, int length) {
    i128 sum = 0;
    i128 term = 1;
    for (int i = 0; i < length; ++i) {
        sum += term;
        if (sum > LIMIT) return LIMIT + 1;
        if (i + 1 < length) {
            term *= ratio;
            if (term > LIMIT) return LIMIT + 1;
        }
    }
    return (int64)sum;
}

int64 randomRepresentable() {
    int ratio;
    if (rnd.next(4) == 0)
        ratio = rnd.next(2, 1000000);
    else if (rnd.next(3) == 0)
        ratio = rnd.next(2, 1000);
    else
        ratio = rnd.next(2, 30);

    vector<int> lengths;
    for (int len = 3; len <= 50; ++len) {
        int64 factor = geometricFactor(ratio, len);
        if (factor > LIMIT) break;
        lengths.push_back(len);
    }

    if (lengths.empty()) {
        ratio = rnd.next(2, 100);
        for (int len = 3; len <= 50; ++len) {
            int64 factor = geometricFactor(ratio, len);
            if (factor > LIMIT) break;
            lengths.push_back(len);
        }
    }

    int length = rnd.any(lengths);
    int64 factor = geometricFactor(ratio, length);
    int64 maxFirst = LIMIT / factor;

    int64 first;
    if (rnd.next(4) == 0)
        first = maxFirst;
    else if (maxFirst <= 1000000)
        first = rnd.next(1LL, maxFirst);
    else
        first = rnd.next(1LL, min<int64>(maxFirst, 1000000LL)) * rnd.next(1LL, maxFirst / min<int64>(maxFirst, 1000000LL));

    return first * factor;
}

int64 randomNearPower() {
    int64 base = rnd.next(2LL, 1000000LL);
    i128 value = 1;
    vector<int64> powers;
    while (value <= LIMIT) {
        powers.push_back((int64)value);
        value *= base;
    }

    int64 center = rnd.any(powers);
    int64 delta = rnd.next(-1000LL, 1000LL);
    return max<int64>(1, min<int64>(LIMIT, center + delta));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int64 n;

    if (mode == 0) {
        n = rnd.next(1LL, min<int64>(1000LL, LIMIT));
    } else if (mode == 1) {
        n = rnd.next(LIMIT - 1000000LL, LIMIT);
    } else if (mode <= 4) {
        n = randomRepresentable();
    } else if (mode == 5) {
        n = randomNearPower();
    } else if (mode == 6) {
        int64 odd = rnd.next(1LL, 500000000000LL) * 2 - 1;
        n = max<int64>(1, min<int64>(LIMIT, odd));
    } else {
        int64 block = rnd.next(1LL, 1000000LL);
        n = rnd.next(1LL, LIMIT / block) * block;
    }

    println(n);
    return 0;
}

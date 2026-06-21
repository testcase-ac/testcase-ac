#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

const int64 MIN_N = 2;
const int64 MAX_N = 1000000000000000LL;

int64 clampN(int64 n) {
    return max(MIN_N, min(MAX_N, n));
}

int64 randomPower4() {
    vector<int64> powers;
    for (int64 x = 1; x <= 2 * MAX_N - 2; x *= 4) {
        powers.push_back(x);
        if (x > (2 * MAX_N - 2) / 4) break;
    }
    return rnd.any(powers);
}

int64 sparseBase4Value() {
    vector<int64> powers;
    for (int64 x = 1; x <= 2 * MAX_N - 2; x *= 4) {
        powers.push_back(x);
        if (x > (2 * MAX_N - 2) / 4) break;
    }

    int take = rnd.next(1, min<int>(6, powers.size()));
    shuffle(powers.begin(), powers.end());

    int64 value = 0;
    for (int i = 0; i < take; ++i) {
        if (value <= 2 * MAX_N - 2 - powers[i]) value += powers[i];
    }
    if (value % 2 == 1) ++value;
    return clampN((value + 2) / 2);
}

int64 makeCase() {
    int mode = rnd.next(0, 7);

    if (mode == 0) return rnd.next(2, 80);

    if (mode == 1) {
        int64 p = randomPower4();
        int64 delta = rnd.next(-8, 8);
        return clampN((p + 2) / 2 + delta);
    }

    if (mode == 2) return sparseBase4Value();

    if (mode == 3) {
        int64 p = randomPower4();
        int64 lo = max<int64>(2, p / 2 - 20);
        int64 hi = min<int64>(MAX_N, p / 2 + 20);
        return rnd.next(lo, hi);
    }

    if (mode == 4) return rnd.next(MAX_N - 1000000, MAX_N);

    if (mode == 5) {
        int64 block = rnd.next(0LL, MAX_N / 1000);
        return clampN(block * 1000 + rnd.next(0, 20));
    }

    if (mode == 6) return rnd.next(2LL, 1000000000LL);

    return rnd.next(2LL, MAX_N);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 80);
    vector<int64> ns;
    ns.reserve(t);

    vector<int64> anchors = {
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        17,
        33,
        MAX_N - 1,
        MAX_N
    };
    shuffle(anchors.begin(), anchors.end());

    for (int64 n : anchors) {
        if ((int)ns.size() == t) break;
        ns.push_back(n);
    }
    while ((int)ns.size() < t) ns.push_back(makeCase());
    shuffle(ns.begin(), ns.end());

    println(t);
    for (int64 n : ns) println(n);

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static long long sumOf(const vector<long long>& values) {
    return accumulate(values.begin(), values.end(), 0LL);
}

static vector<long long> makeNoOneSet() {
    int c = rnd.next(1, 8);
    vector<long long> values;
    values.reserve(c);

    long long base = rnd.next(2, 20);
    for (int i = 0; i < c; ++i) {
        values.push_back(base + rnd.next(0, 30));
    }
    return values;
}

static vector<long long> makeDensePrefixSet() {
    int c = rnd.next(2, 16);
    vector<long long> values;
    values.reserve(c);

    long long reachable = 0;
    for (int i = 0; i < c; ++i) {
        long long hi = min(reachable + 1, 50LL);
        long long value = rnd.next(1LL, hi);
        values.push_back(value);
        reachable += value;
    }
    return values;
}

static vector<long long> makeDuplicateHeavySet() {
    int c = rnd.next(5, 30);
    int kinds = rnd.next(1, 4);
    vector<long long> pool;
    for (int i = 0; i < kinds; ++i) {
        pool.push_back(rnd.next(1, 12));
    }

    vector<long long> values;
    values.reserve(c);
    for (int i = 0; i < c; ++i) {
        values.push_back(rnd.any(pool));
    }
    return values;
}

static vector<long long> makeGapAfterPrefixSet() {
    int prefix = rnd.next(1, 8);
    int extra = rnd.next(1, 8);
    vector<long long> values;
    values.reserve(prefix + extra);

    long long reachable = 0;
    for (int i = 0; i < prefix; ++i) {
        long long value = rnd.next(1LL, reachable + 1);
        values.push_back(value);
        reachable += value;
    }

    long long gapStart = reachable + rnd.next(2LL, 20LL);
    for (int i = 0; i < extra; ++i) {
        values.push_back(gapStart + rnd.next(0LL, 40LL));
    }
    return values;
}

static vector<long long> makeNearLimitSet() {
    int c = rnd.next(2, 12);
    vector<long long> values;
    values.reserve(c);

    long long remaining = 1000000000LL;
    for (int i = 0; i < c; ++i) {
        int slotsLeft = c - i;
        long long minAfter = slotsLeft - 1;
        long long cap = min(remaining - minAfter, 300000000LL);
        long long value = (i == 0 && rnd.next(2) == 0) ? 1 : rnd.next(1LL, cap);
        values.push_back(value);
        remaining -= value;
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    println(n);

    for (int set = 0; set < n; ++set) {
        int mode = rnd.next(0, 4);
        vector<long long> values;

        if (mode == 0) {
            values = makeNoOneSet();
        } else if (mode == 1) {
            values = makeDensePrefixSet();
        } else if (mode == 2) {
            values = makeDuplicateHeavySet();
        } else if (mode == 3) {
            values = makeGapAfterPrefixSet();
        } else {
            values = makeNearLimitSet();
        }

        while (sumOf(values) > 1000000000LL) {
            values.pop_back();
        }
        shuffle(values.begin(), values.end());

        println(static_cast<int>(values.size()));
        println(values);
    }

    return 0;
}

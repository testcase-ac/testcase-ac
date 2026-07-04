#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

constexpr long long kMaxValue = 1000000000000000LL;

long long randomValueForMode(int mode) {
    if (mode == 0) return rnd.next(0LL, 30LL);
    if (mode == 1) return rnd.next(0LL, 100LL);
    if (mode == 2) return rnd.next(0LL, 4095LL);

    vector<long long> anchors = {
        0LL,
        1LL,
        2LL,
        3LL,
        15LL,
        31LL,
        63LL,
        127LL,
        255LL,
        1023LL,
        (1LL << 20) - 1,
        (1LL << 40) - 1,
        kMaxValue,
    };

    long long base = rnd.any(anchors);
    long long wiggle = rnd.next(0LL, 2000LL);
    if (rnd.next(2) == 0) return max(0LL, base - wiggle);
    return min(kMaxValue, base + wiggle);
}

long long xorSum(const vector<long long>& values, long long k) {
    long long sum = 0;
    for (long long value : values) sum += value ^ k;
    return sum;
}

long long chooseM(const vector<long long>& values, int mode) {
    vector<long long> probes = {
        0LL,
        1LL,
        3LL,
        7LL,
        15LL,
        31LL,
        63LL,
        127LL,
        255LL,
        1023LL,
        (1LL << 20) - 1,
        (1LL << 40) - 1,
    };

    long long smallest = kMaxValue;
    for (long long k : probes) smallest = min(smallest, xorSum(values, k));

    if (mode == 0) return rnd.next(0LL, min(kMaxValue, smallest + 20));
    if (mode == 1) return min(kMaxValue, smallest + rnd.next(0LL, 500LL));
    if (mode == 2) return rnd.next(0LL, 100000LL);

    vector<long long> choices = {
        0LL,
        smallest,
        min(kMaxValue, smallest + rnd.next(0LL, 1000000LL)),
        kMaxValue,
    };
    return rnd.any(choices);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (mode == 4) {
            n = rnd.next(25, 80);
        } else {
            n = rnd.next(1, 12);
        }

        vector<long long> values;
        values.reserve(n);
        for (int i = 0; i < n; ++i) values.push_back(randomValueForMode(mode));

        if (mode == 3 && n >= 4) {
            values[0] = 0;
            values[1] = kMaxValue;
            values[2] = (1LL << 49) - 1;
            values[3] = kMaxValue - 1;
        }

        shuffle(values.begin(), values.end());
        long long m = chooseM(values, mode);

        println(n, m);
        println(values);
    }

    return 0;
}

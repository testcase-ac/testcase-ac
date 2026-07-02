#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000LL;

bool isPractical(long long n) {
    vector<long long> divisors;
    for (long long d = 1; d * d <= n; ++d) {
        if (n % d != 0) {
            continue;
        }
        divisors.push_back(d);
        if (d * d != n) {
            divisors.push_back(n / d);
        }
    }

    sort(divisors.begin(), divisors.end());

    long long covered = 0;
    for (long long d : divisors) {
        if (covered + 1 < d) {
            return false;
        }
        covered += d;
        if (covered >= n - 1) {
            return true;
        }
    }
    return true;
}

long long randomSmall() {
    int mode = rnd.next(4);
    if (mode == 0) {
        return rnd.next(1, 80);
    }
    if (mode == 1) {
        return rnd.next(81, 5000);
    }
    if (mode == 2) {
        return rnd.next(1, 250) * 2LL;
    }
    return rnd.next(1, 80) * rnd.next(1, 80);
}

long long randomLargeComposite() {
    long long base = rnd.next(100000, 1000000);
    long long multiplier = rnd.next(2, 1000);
    long long value = base * multiplier;
    if (rnd.next(2) == 0) {
        value *= rnd.next(2, 20);
    }
    return min(value, LIMIT);
}

long long randomNearLimit() {
    return LIMIT - rnd.next(0, 250000);
}

long long makePracticalFromPowers() {
    long long value = 1;
    int twos = rnd.next(1, 20);
    for (int i = 0; i < twos && value <= LIMIT / 2; ++i) {
        value *= 2;
    }

    vector<int> factors = {3, 5, 7, 11, 13};
    shuffle(factors.begin(), factors.end());
    for (int p : factors) {
        int repeats = rnd.next(0, 3);
        for (int i = 0; i < repeats && value <= LIMIT / p; ++i) {
            value *= p;
        }
    }

    return value;
}

long long chooseTimestamp() {
    int mode = rnd.next(8);
    if (mode == 0) {
        return rnd.next(1, 2) == 1 ? 1 : 2;
    }
    if (mode == 1) {
        return randomSmall();
    }
    if (mode == 2) {
        return makePracticalFromPowers();
    }
    if (mode == 3) {
        long long candidate = makePracticalFromPowers() + rnd.next(1, 20);
        return min(candidate, LIMIT);
    }
    if (mode == 4) {
        return 2LL * rnd.next(1, 500000000);
    }
    if (mode == 5) {
        return 2LL * rnd.next(1, 500000) + 1;
    }
    if (mode == 6) {
        return randomLargeComposite();
    }
    return randomNearLimit();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 35);
    vector<long long> values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(4);
    values.push_back(6);
    values.push_back(10);
    values.push_back(12);
    values.push_back(LIMIT);

    while ((int)values.size() < t) {
        long long value = chooseTimestamp();
        if (rnd.next(5) == 0) {
            long long start = rnd.next(1, 2000);
            value = start + (int)values.size() % 9;
        }
        if (rnd.next(6) == 0 && !isPractical(value)) {
            value = max(1LL, value - 1);
        }
        values.push_back(max(1LL, min(value, LIMIT)));
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (long long value : values) {
        println(value);
    }

    return 0;
}

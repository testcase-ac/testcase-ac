#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long gcdll(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void addUnique(vector<long long>& values, long long x) {
    if (x < 1 || x > LIMIT) return;
    if (find(values.begin(), values.end(), x) == values.end()) values.push_back(x);
}

long long boundedMul(long long a, long long b) {
    if (a > LIMIT / b) return LIMIT;
    return a * b;
}

long long randomPower(long long base) {
    long long value = 1;
    int maxExp = 0;
    while (value <= LIMIT / base) {
        value *= base;
        ++maxExp;
    }
    int exp = rnd.next(1, maxExp);
    value = 1;
    for (int i = 0; i < exp; ++i) value *= base;
    return value;
}

long long intervalLcm(int l, int r) {
    long long value = 1;
    for (int x = l; x <= r; ++x) {
        long long g = gcdll(value, x);
        if (value / g > LIMIT / x) return LIMIT;
        value = value / g * x;
    }
    return value;
}

long long smoothNumber() {
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    shuffle(primes.begin(), primes.end());

    long long value = 1;
    int used = rnd.next(2, 6);
    for (int i = 0; i < used; ++i) {
        int p = primes[i];
        int repeats = rnd.next(1, 4);
        for (int j = 0; j < repeats && value <= LIMIT / p; ++j) value *= p;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> values;
    addUnique(values, 1);
    addUnique(values, 2);
    addUnique(values, 3);
    addUnique(values, 4);
    addUnique(values, 12);
    addUnique(values, 17);
    addUnique(values, 504);
    addUnique(values, 999999999999999937LL);
    addUnique(values, LIMIT);

    int intervalCases = rnd.next(4, 16);
    for (int i = 0; i < intervalCases; ++i) {
        int l = rnd.next(1, 80);
        int len = rnd.next(1, 12);
        addUnique(values, intervalLcm(l, l + len));
    }

    vector<long long> primeBases = {2, 3, 5, 7, 11, 13, 17, 19, 31, 37};
    int powerCases = rnd.next(4, 14);
    for (int i = 0; i < powerCases; ++i) {
        long long base = rnd.any(primeBases);
        long long power = randomPower(base);
        int multiplier = rnd.next(1, 2000);
        addUnique(values, power);
        addUnique(values, boundedMul(power, multiplier));
    }

    int smoothCases = rnd.next(8, 28);
    for (int i = 0; i < smoothCases; ++i) addUnique(values, smoothNumber());

    int randomCases = rnd.next(8, 32);
    for (int i = 0; i < randomCases; ++i) {
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            addUnique(values, rnd.next(1LL, 1000000LL));
        } else if (mode == 1) {
            addUnique(values, rnd.next(1LL, 1000000000000LL));
        } else if (mode == 2) {
            long long delta = rnd.next(0LL, 1000000LL);
            addUnique(values, LIMIT - delta);
        } else {
            addUnique(values, rnd.next(1LL, LIMIT));
        }
    }

    shuffle(values.begin(), values.end());
    int z = rnd.next(1, min<int>(100, values.size()));
    values.resize(z);

    println(z);
    for (long long value : values) println(value);

    return 0;
}

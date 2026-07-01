#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long clampToBounds(long long x) {
    return max(0LL, min(LIMIT, x));
}

long long powerOfFour(int exponent) {
    long long value = 1;
    for (int i = 0; i < exponent; ++i) value *= 4;
    return value;
}

long long randomNearPowerOfFour() {
    int exponent = rnd.next(0, 29);
    long long base = powerOfFour(exponent);
    long long width = min(1000LL, max(8LL, base / 4));
    return clampToBounds(base + rnd.next(-width, width));
}

long long randomStructuredValue() {
    int mode = rnd.next(0, 6);

    if (mode == 0) return rnd.next(0LL, 100LL);
    if (mode == 1) return randomNearPowerOfFour();
    if (mode == 2) {
        long long q = rnd.next(0LL, LIMIT / 16);
        return clampToBounds(q * 16 + rnd.next(0LL, 15LL));
    }
    if (mode == 3) {
        long long q = rnd.next(0LL, LIMIT / 4);
        return clampToBounds(q * 4 + rnd.next(0LL, 3LL));
    }
    if (mode == 4) return LIMIT - rnd.next(0LL, 1000LL);
    if (mode == 5) return rnd.next(0LL, LIMIT);

    int exponent = rnd.next(0, 29);
    long long base = powerOfFour(exponent);
    long long multiplier = rnd.next(0LL, max(1LL, LIMIT / base));
    return clampToBounds(base * multiplier);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    vector<long long> values;
    values.push_back(0);
    values.push_back(1);
    values.push_back(4);
    values.push_back(LIMIT);

    while ((int)values.size() < t) values.push_back(randomStructuredValue());
    shuffle(values.begin(), values.end());

    println(t);
    for (long long value : values) println(value);

    return 0;
}

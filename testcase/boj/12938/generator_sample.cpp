#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedPower(int base, int maxValue) {
    int value = 1;
    int limit = 0;
    while (value <= maxValue / base) {
        value *= base;
        ++limit;
    }

    int exponent = rnd.next(0, limit);
    value = 1;
    for (int i = 0; i < exponent; ++i) {
        value *= base;
    }
    return value;
}

int randomComposite(const vector<int>& primes) {
    int value = 1;
    int factors = rnd.next(1, 8);
    for (int i = 0; i < factors; ++i) {
        int p = rnd.any(primes);
        if (value > 1000000000 / p) {
            break;
        }
        value *= p;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    const vector<int> largeValues = {
        999999937, 1000000000, 999999929, 999983, 99991, 65536, 59049
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 1) {
        n = rnd.next(120, 500);
    } else {
        n = rnd.next(1, 30);
    }

    vector<int> values;
    values.reserve(n);

    for (int i = 0; i < n; ++i) {
        int value = 1;

        if (mode == 0) {
            value = rnd.next(0, 4) == 0 ? rnd.any(smallPrimes) : 1;
        } else if (mode == 1) {
            value = rnd.next(0, 3) == 0 ? rnd.any(largeValues) : 1;
        } else if (mode == 2) {
            value = boundedPower(rnd.any(vector<int>{2, 3, 5}), 1000000000);
        } else if (mode == 3) {
            value = randomComposite(smallPrimes);
        } else if (mode == 4) {
            int a = randomComposite(smallPrimes);
            int b = rnd.any(vector<int>{1, 9973, 99991, 999983});
            value = a <= 1000000000 / b ? a * b : a;
        } else {
            value = rnd.next(1, 1000000000);
        }

        values.push_back(value);
    }

    if (rnd.next(0, 1)) {
        shuffle(values.begin(), values.end());
    }

    println(n);
    println(values);

    return 0;
}

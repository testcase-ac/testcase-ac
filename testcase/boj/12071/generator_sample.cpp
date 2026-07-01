#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long LIMIT = 1000000000000000LL;

long long randomPrimePower() {
    vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    long long p = rnd.any(primes);
    long long value = p;
    while (value <= LIMIT / p && rnd.next(0, 2) != 0) value *= p;
    return value;
}

long long randomCompositeProduct() {
    int count = rnd.next(2, 7);
    long long value = 1;
    for (int i = 0; i < count; ++i) {
        long long factor = randomPrimePower();
        if (value <= LIMIT / factor) value *= factor;
    }
    if (value < 2) return rnd.next(2, 1000000);
    return value;
}

long long randomDigitPattern() {
    int digits = rnd.next(1, 15);
    long long value = 0;
    for (int i = 0; i < digits; ++i) {
        int digit;
        if (i == 0) {
            digit = rnd.next(1, 9);
        } else if (rnd.next(0, 3) == 0) {
            digit = rnd.any(vector<int>{0, 1, 8, 9});
        } else {
            digit = rnd.next(0, 9);
        }
        value = value * 10 + digit;
    }
    return max(2LL, value);
}

long long randomNearLimit() {
    long long offset = rnd.next(0LL, 1000000LL);
    long long value = LIMIT - offset;
    if (value < 2) value = 2;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    vector<long long> values;
    values.reserve(t);

    vector<long long> anchors = {
        2,
        4,
        30,
        36300,
        LIMIT,
        999999999999999LL,
        999999999999983LL,
    };

    shuffle(anchors.begin(), anchors.end());
    int anchorCount = rnd.next(1, min((int)anchors.size(), t / 2));
    for (int i = 0; i < anchorCount; ++i) values.push_back(anchors[i]);

    while ((int)values.size() < t) {
        int mode = rnd.next(0, 5);
        long long n;
        if (mode == 0) {
            n = rnd.next(2, 200);
        } else if (mode == 1) {
            n = randomPrimePower();
        } else if (mode == 2) {
            n = randomCompositeProduct();
        } else if (mode == 3) {
            n = randomDigitPattern();
        } else if (mode == 4) {
            n = randomNearLimit();
        } else {
            n = rnd.next(2LL, LIMIT);
        }
        values.push_back(n);
    }

    shuffle(values.begin(), values.end());

    println(t);
    for (long long n : values) println(n);

    return 0;
}

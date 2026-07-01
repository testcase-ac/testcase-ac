#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

const int kMaxN = 2147483647;

int randomPrime() {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
        37, 41, 43, 47, 53, 59, 61, 67, 71, 73
    };
    return rnd.any(primes);
}

int randomPrimePower() {
    int p = randomPrime();
    int64_t value = p;
    vector<int> powers;
    while (value <= kMaxN) {
        powers.push_back(static_cast<int>(value));
        if (value > kMaxN / p) break;
        value *= p;
    }
    return rnd.any(powers);
}

int randomFactoredNumber() {
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    shuffle(primes.begin(), primes.end());

    int64_t value = 1;
    int factorCount = rnd.next(2, 6);
    int exponentBias = rnd.next(0, 2);
    for (int i = 0; i < factorCount; ++i) {
        int exponent = exponentBias == 0 ? rnd.next(1, 2) : rnd.next(1, 5);
        for (int j = 0; j < exponent && value <= kMaxN / primes[i]; ++j) {
            value *= primes[i];
        }
    }
    return static_cast<int>(max<int64_t>(2, value));
}

int randomNearLimitComposite() {
    int p = rnd.any(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29});
    int q = rnd.next(max(2, kMaxN / p - 2000), kMaxN / p);
    return p * q;
}

int randomN() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return rnd.any(vector<int>{2, 3, 4, 6, 8, 12, 16, 32});
    if (mode == 1) return randomPrimePower();
    if (mode == 2) return randomFactoredNumber();
    if (mode == 3) return randomNearLimitComposite();
    if (mode == 4) return rnd.next(2, 100000);
    return rnd.any(vector<int>{2147483647, 2147483646, 1073741824, 1073741823});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 35);
    println(t);
    for (int i = 0; i < t; ++i) {
        string firstPlayer = rnd.next(0, 1) == 0 ? "Alice" : "Bob";
        println(randomN(), firstPlayer);
    }

    return 0;
}

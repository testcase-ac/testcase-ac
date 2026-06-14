#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1000000000;

long long clampProduct(long long value, int factor) {
    if (value > MAX_N / factor) {
        return value;
    }
    return value * factor;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = 1;

    if (mode == 0) {
        vector<int> edgeValues = {1, 2, 3, 4, 5, 12, 36, MAX_N};
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        long long value = 1;
        int p = rnd.any(primes);
        int exponent = rnd.next(1, 18);
        for (int i = 0; i < exponent && value <= MAX_N / p; ++i) {
            value *= p;
        }
        n = static_cast<int>(value);
    } else if (mode == 2) {
        vector<int> factors = {2, 3, 4, 5, 6, 8, 9, 10, 12};
        long long value = 1;
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            int factor = rnd.any(factors);
            if (value <= MAX_N / factor) {
                value *= factor;
            }
        }
        n = static_cast<int>(value);
    } else if (mode == 3) {
        vector<int> smooth = {720, 840, 1260, 1680, 2520, 5040, 7560, 10080};
        long long value = rnd.any(smooth);
        int multiplier = rnd.next(1, 1000);
        if (value <= MAX_N / multiplier) {
            value *= multiplier;
        }
        n = static_cast<int>(value);
    } else if (mode == 4) {
        int base = rnd.next(1, 31623);
        n = base * base;
    } else if (mode == 5) {
        vector<int> nearLimit = {
            MAX_N,
            MAX_N - 1,
            MAX_N - rnd.next(0, 1000000),
            rnd.next(900000000, MAX_N)
        };
        n = rnd.any(nearLimit);
    } else if (mode == 6) {
        int a = rnd.next(1, 100000);
        int b = rnd.next(1, MAX_N / a);
        n = a * b;
    } else {
        n = rnd.next(1, MAX_N);
    }

    println(n);
    return 0;
}

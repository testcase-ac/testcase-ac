#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0 ? rnd.next(1, 4) : rnd.next(5, 28));
    vector<long long> a;
    a.reserve(n);

    const vector<long long> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
    };
    const vector<long long> special = {
        1, 2, 3, 4, 6, 7, 10, 12, 30, 210, 999999937LL, 1000000000LL
    };

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(special));
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a.push_back(primes[i % (int)primes.size()]);
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        long long factor = rnd.any(primes);
        for (int i = 0; i < n; ++i) {
            a.push_back(factor * rnd.next(1LL, 1000000000LL / factor));
        }
    } else if (mode == 3) {
        long long leftFactor = rnd.any(primes);
        long long rightFactor = rnd.any(primes);
        while (rightFactor == leftFactor) {
            rightFactor = rnd.any(primes);
        }
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) {
            long long factor = (i < split ? leftFactor : rightFactor);
            a.push_back(factor * rnd.next(1, 20000000));
        }
        shuffle(a.begin(), a.begin() + split);
        shuffle(a.begin() + split, a.end());
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            long long base = rnd.any(primes);
            int exponent = rnd.next(1, 8);
            long long value = 1;
            while (exponent-- > 0 && value <= 1000000000LL / base) {
                value *= base;
            }
            a.push_back(value);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(1);
            } else if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.any(primes) * rnd.next(1, 1000));
            } else {
                a.push_back(rnd.next(1, 1000000000));
            }
        }
    } else {
        long long low = rnd.next(1, 1000);
        long long high = rnd.next(low, min(1000000000LL, low + rnd.next(20, 5000)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(low, high));
        }
    }

    if (rnd.next(0, 3) == 0) {
        reverse(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long boundedMul(long long a, long long b) {
    if (a > LIMIT / b) {
        return LIMIT + 1;
    }
    return a * b;
}

long long primePower(long long p) {
    long long x = 1;
    int exponent = rnd.next(1, 60);
    for (int i = 0; i < exponent; ++i) {
        long long next = boundedMul(x, p);
        if (next > LIMIT) {
            break;
        }
        x = next;
    }
    return x;
}

long long smallPrimeProduct(const vector<long long>& primes) {
    vector<long long> shuffled = primes;
    shuffle(shuffled.begin(), shuffled.end());

    long long x = 1;
    int factors = rnd.next(1, 12);
    for (int i = 0; i < factors; ++i) {
        long long p = shuffled[i % static_cast<int>(shuffled.size())];
        int repeats = rnd.next(1, 5);
        for (int j = 0; j < repeats; ++j) {
            long long next = boundedMul(x, p);
            if (next > LIMIT) {
                break;
            }
            x = next;
        }
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    vector<long long> notable = {
        1,
        2,
        3,
        4,
        5,
        6,
        10,
        45,
        99,
        9999999967LL,
        999999937LL * 999999937LL,
        999999929LL * 999999937LL,
        999999999999999937LL,
        999999999999999989LL,
        LIMIT - 1,
        LIMIT};

    int mode = rnd.next(0, 6);
    long long n = 1;

    if (mode == 0) {
        n = rnd.any(notable);
    } else if (mode == 1) {
        n = rnd.next(1LL, 1000000LL);
    } else if (mode == 2) {
        n = rnd.next(1LL, LIMIT);
    } else if (mode == 3) {
        n = primePower(rnd.any(smallPrimes));
    } else if (mode == 4) {
        n = smallPrimeProduct(smallPrimes);
    } else if (mode == 5) {
        long long base = rnd.next(1LL, 1000000000LL);
        n = base * base;
    } else {
        long long offset = rnd.next(0LL, 1000000LL);
        n = LIMIT - offset;
    }

    println(n);
    return 0;
}

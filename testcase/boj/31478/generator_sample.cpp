#include "testlib.h"
#include <vector>

using namespace std;

long long modPow(long long base, long long exponent, long long mod) {
    long long result = 1 % mod;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

int inverseMod7(int value) {
    for (int candidate = 1; candidate < 7; ++candidate) {
        if (value * candidate % 7 == 1) {
            return candidate;
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> divisors = {1, 2, 3, 4, 5, 6};
    int a = rnd.any(divisors);
    long long b = 1;
    long long c = 1;

    int mode = rnd.next(0, 6);
    if (a == 1) {
        b = rnd.next(1, 100);
        c = rnd.next(1, 100);
    } else if (mode == 0) {
        b = a;
        c = rnd.next(1, 100);
    } else if (mode == 1) {
        b = 1LL * a * rnd.next(1, 20);
        c = rnd.next(1, 100);
    } else if (a == 4 && mode <= 3) {
        b = 2LL * rnd.next(1, 50);
        c = rnd.next(2, 100);
    } else if (a == 6 && mode <= 3) {
        b = 6LL * rnd.next(1, 16);
        c = rnd.next(1, 100);
    } else if (mode == 4) {
        b = 1000000000LL / a * a;
        c = rnd.next(1, 1000000000);
    } else if (mode == 5) {
        b = a;
        c = 1000000000LL;
    } else {
        b = a;
        c = rnd.next(1, 1000000000);
    }

    int firstOffset = modPow(a, modPow(b, c, 6), 7);
    int secondOffset = modPow(b, c, 7) * inverseMod7(a) % 7;

    int k = rnd.next(0, 6);
    int category = rnd.next(0, 3);
    int l = rnd.next(0, 6);
    if (category == 1) {
        l = (k + firstOffset) % 7;
        if (firstOffset == secondOffset && rnd.next(0, 1) == 0) {
            category = 3;
        }
    } else if (category == 2) {
        l = (k + secondOffset) % 7;
        if (firstOffset == secondOffset && rnd.next(0, 1) == 0) {
            category = 3;
        }
    } else if (category == 3 && firstOffset == secondOffset) {
        l = (k + firstOffset) % 7;
    }

    if (category == 0 || (category == 3 && firstOffset != secondOffset)) {
        while (l == (k + firstOffset) % 7 || l == (k + secondOffset) % 7) {
            l = rnd.next(0, 6);
        }
    }

    println(a, b, c);
    println(k, l);

    return 0;
}

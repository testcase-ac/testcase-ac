#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

using int64 = long long;
using i128 = __int128_t;

const int64 MAX_Z = 1000000000000000000LL;

int64 modPow(int64 a, int64 e, int64 mod) {
    i128 result = 1;
    i128 base = a % mod;
    while (e > 0) {
        if (e & 1) result = result * base % mod;
        base = base * base % mod;
        e >>= 1;
    }
    return (int64)result;
}

bool isPrime(int64 n) {
    if (n < 2) return false;
    for (int64 p : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (n % p == 0) return n == p;
    }

    int64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    for (int64 a : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL}) {
        if (a >= n) continue;
        int64 x = modPow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = (int64)((i128)x * x % n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int64 nextPrime(int64 n) {
    if (n <= 2) return 2;
    if ((n & 1) == 0) ++n;
    while (!isPrime(n)) n += 2;
    return n;
}

int64 randomZNearConsecutivePrimeProduct() {
    int64 center = rnd.next(2, 999999000);
    int64 p = nextPrime(center);
    int64 q = nextPrime(p + 1);
    i128 product = (i128)p * q;

    if (product > MAX_Z) return rnd.next(6LL, MAX_Z);

    int64 delta = rnd.next(-25, 25);
    int64 z = (int64)product + delta;
    return max(6LL, min(MAX_Z, z));
}

int64 randomZ() {
    int mode = rnd.next(0, 8);
    if (mode == 0) return rnd.any(vector<int64>{6, 7, 14, 15, 2020, 2021, MAX_Z});
    if (mode == 1) return rnd.next(6LL, 2021LL);
    if (mode == 2) return rnd.next(6LL, 1000000LL);
    if (mode == 3) return rnd.next(100000000LL, 1000000000LL);
    if (mode == 4) return rnd.next(999999000000000000LL, MAX_Z);
    return randomZNearConsecutivePrimeProduct();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 25);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        println(randomZ());
    }

    return 0;
}

#include "testlib.h"

#include <cstdint>

using namespace std;

bool isPrime(long long x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    for (long long d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 100, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        long long key = inf.readLong(9LL, 4294967295LL, "public_key");
        inf.readEoln();

        bool valid = false;
        for (long long factor = 3; factor * factor <= key; factor += 2) {
            if (key % factor != 0) continue;

            long long other = key / factor;
            valid = factor > 2 && other > 2 && isPrime(factor) && isPrime(other);
            break;
        }

        ensuref(valid, "public key at line %d is not a product of exactly two primes greater than 2: %lld", i + 2, key);
    }

    inf.readEof();
}

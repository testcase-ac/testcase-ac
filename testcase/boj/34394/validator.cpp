#include "testlib.h"

#include <set>

using namespace std;

const long long LIMIT = 1000000000000000LL;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    while (exp > 0) {
        if (exp & 1LL) {
            result = static_cast<long long>((__int128)result * base % mod);
        }
        base = static_cast<long long>((__int128)base * base % mod);
        exp >>= 1LL;
    }
    return result;
}

bool isPrime(long long value) {
    if (value < 2) {
        return false;
    }
    for (long long prime : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (value == prime) {
            return true;
        }
        if (value % prime == 0) {
            return false;
        }
    }

    long long d = value - 1;
    int shifts = 0;
    while ((d & 1LL) == 0) {
        d >>= 1LL;
        ++shifts;
    }

    for (long long base : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (base >= value) {
            continue;
        }
        long long x = modPow(base, d, value);
        if (x == 1 || x == value - 1) {
            continue;
        }

        bool witness = true;
        for (int r = 1; r < shifts; ++r) {
            x = static_cast<long long>((__int128)x * x % value);
            if (x == value - 1) {
                witness = false;
                break;
            }
        }
        if (witness) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    long long t = inf.readLong(1LL, LIMIT, "T");
    inf.readEoln();

    set<long long> cycles;
    long long product = 1;
    for (int i = 1; i <= n; ++i) {
        long long c = inf.readLong(2LL, LIMIT, "C");
        inf.readEoln();

        ensuref(isPrime(c), "cycle length %d is not prime: %lld", i, c);
        ensuref(cycles.insert(c).second, "duplicate cycle length at index %d: %lld", i, c);
        ensuref(product <= LIMIT / c,
                "product of cycle lengths exceeds 10^15 after index %d", i);
        product *= c;
    }

    inf.readEof();
}

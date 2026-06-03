#include "testlib.h"

using namespace std;

long long mod_pow(long long base, long long exponent, long long mod) {
    long long result = 1 % mod;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1LL) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        exponent >>= 1LL;
    }
    return result;
}

bool is_prime(int value) {
    if (value < 2) return false;
    if (value == 2 || value == 3) return true;
    if (value % 2 == 0) return false;

    int d = value - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        ++s;
    }

    const int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int base : bases) {
        if (base >= value) break;

        long long x = mod_pow(base, d, value);
        if (x == 1 || x == value - 1) continue;

        bool witness_passed = false;
        for (int r = 1; r < s; ++r) {
            x = (__int128)x * x % value;
            if (x == value - 1) {
                witness_passed = true;
                break;
            }
        }
        if (!witness_passed) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 2, "n");
    inf.readEoln();

    for (int i = 0; i <= n; ++i) {
        if (i > 0) inf.readSpace();
        inf.readInt(1, 2000000000, "a_i");
    }
    inf.readEoln();

    int m = inf.readInt(2, 1999999999, "m");
    inf.readEoln();
    ensuref(is_prime(m), "m must be prime, but got %d", m);

    inf.readEof();
}

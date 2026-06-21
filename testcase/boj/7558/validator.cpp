#include "testlib.h"

using namespace std;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

bool isPrime(int n) {
    if (n < 2) {
        return false;
    }
    if (n % 2 == 0) {
        return n == 2;
    }

    int d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        ++s;
    }

    for (int a : {2, 3, 5, 7}) {
        if (a >= n) {
            continue;
        }
        long long x = modPow(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = (__int128)x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of scenarios; use the local
    // default cap for unspecified test case counts.
    int scenarios = inf.readInt(1, 100000, "scenarios");
    inf.readEoln();

    for (int i = 1; i <= scenarios; ++i) {
        setTestCase(i);

        int a = inf.readInt(-1000000000, 1000000000, "a");
        inf.readSpace();
        int p = inf.readInt(3, 999999999, "p");
        inf.readEoln();

        ensuref(p % 2 == 1, "p must be odd: %d", p);
        ensuref(isPrime(p), "p must be prime: %d", p);
        long long normalizedA = a % (long long)p;
        if (normalizedA < 0) {
            normalizedA += p;
        }
        ensuref(normalizedA != 0, "a must not be divisible by p: a=%d, p=%d", a, p);
    }

    inf.readEof();
}

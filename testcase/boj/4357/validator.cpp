#include "testlib.h"

using namespace std;

static long long modPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

static bool isPrime(long long n) {
    if (n < 2) {
        return false;
    }
    for (long long p : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (n == p) {
            return true;
        }
        if (n % p == 0) {
            return false;
        }
    }

    long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    for (long long a : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
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

    int caseCount = 0;
    while (!inf.seekEof()) {
        ++caseCount;
        setTestCase(caseCount);
        // CHECK: The statement gives no case-count limit; use the repo default cap.
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);

        long long p = inf.readLong(3LL, 2147483647LL, "P");
        inf.readSpace();
        inf.readLong(2LL, p - 1, "B");
        inf.readSpace();
        inf.readLong(1LL, p - 1, "N");
        inf.readEoln();

        ensuref(isPrime(p), "P must be prime: %lld", p);
    }

    ensuref(caseCount > 0, "input must contain at least one test case");
    inf.readEof();
}

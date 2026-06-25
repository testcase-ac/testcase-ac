#include "testlib.h"

#include <numeric>

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 997 * 991, "n");
        inf.readSpace();
        int e = inf.readInt(1, 997 * 991, "e");
        inf.readEoln();

        int p = -1;
        int q = -1;
        for (int candidate = 2; candidate < 1000; ++candidate) {
            if (n % candidate != 0) {
                continue;
            }
            int other = n / candidate;
            if (other < 1000 && candidate != other && isPrime(candidate) && isPrime(other)) {
                p = candidate;
                q = other;
                break;
            }
        }

        ensuref(p != -1,
                "n must be the product of two distinct primes below 1000, got %d",
                n);

        int phi = (p - 1) * (q - 1);
        ensuref(1 < e && e < phi, "e must satisfy 1 < e < phi(n), got e=%d phi=%d", e, phi);
        ensuref(gcd(e, phi) == 1, "d must exist for e=%d phi=%d", e, phi);
    }

    inf.readEof();
}

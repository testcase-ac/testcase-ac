#include "testlib.h"

#include <numeric>

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; 1LL * d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(15, 1000000000, "N");
    inf.readSpace();
    int e = inf.readInt(1, n - 1, "E");
    inf.readSpace();
    inf.readInt(1, n - 1, "C");
    inf.readEoln();
    inf.readEof();

    int p = -1;
    for (int d = 3; 1LL * d * d <= n; d += 2) {
        if (n % d == 0) {
            p = d;
            break;
        }
    }
    ensuref(p != -1, "N must be a product of two odd primes");

    int q = n / p;
    ensuref(p % 2 == 1 && q % 2 == 1, "P and Q must be odd");
    ensuref(isPrime(p) && isPrime(q), "N must be a product of two odd primes");
    // CHECK: RSA uses two different primes P and Q; the statement's phi(N)=(P-1)(Q-1)
    // formula is the semiprime RSA construction, not the square-prime totient.
    ensuref(p != q, "P and Q must be distinct");

    long long phi = 1LL * (p - 1) * (q - 1);
    ensuref(1 < e && e < phi, "E must satisfy 1 < E < phi(N)");
    ensuref(gcd<long long>(phi, e) == 1, "gcd(phi(N), E) must be 1");
}

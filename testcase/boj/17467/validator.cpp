#include "testlib.h"
#include <cmath>

using namespace std;

// Miller-Rabin primality test for 32-bit numbers
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    int d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // Deterministic bases for 32-bit integers
    int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int a : bases) {
        if (a >= n) break;
        long long x = 1, p = d;
        long long base = a;
        int mod = n;
        // Compute x = base^p % mod
        while (p) {
            if (p & 1) x = (x * base) % mod;
            base = (base * base) % mod;
            p >>= 1;
        }
        if (x == 1 || x == n - 1) continue;
        bool witness = false;
        for (int r = 1; r < s; ++r) {
            x = (x * x) % n;
            if (x == n - 1) {
                witness = true;
                break;
            }
        }
        if (!witness) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000000000, "N");
    inf.readSpace();
    int P = inf.readInt(N+1, 1000000000, "P");
    inf.readEoln();

    ensuref(is_prime(P), "P=%d is not a prime number", P);

    inf.readEof();
}

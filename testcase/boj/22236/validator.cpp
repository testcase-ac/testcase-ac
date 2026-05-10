#include "testlib.h"
#include <cmath>
using namespace std;

// Miller-Rabin primality test for 32-bit integers
bool is_prime(int m) {
    if (m < 2) return false;
    if (m == 2 || m == 3) return true;
    if (m % 2 == 0) return false;
    int d = m - 1, s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    // Deterministic for m < 2e9 with these bases
    int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int a : bases) {
        if (a >= m) break;
        long long x = 1, p = d, base = a;
        while (p) {
            if (p & 1) x = (x * base) % m;
            base = (base * base) % m;
            p >>= 1;
        }
        if (x == 1 || x == m - 1) continue;
        bool ok = false;
        for (int r = 1; r < s; ++r) {
            x = (x * x) % m;
            if (x == m - 1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d = inf.readInt(1, 4000, "d");
    inf.readSpace();
    int m = inf.readInt(2, 2000000000, "m");
    inf.readEoln();

    ensuref(d % 2 == 0, "d must be even, but got d = %d", d);
    ensuref(is_prime(m), "m must be prime, but got m = %d", m);

    inf.readEof();
}

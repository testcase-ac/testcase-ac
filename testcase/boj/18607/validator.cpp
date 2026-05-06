#include "testlib.h"
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

// Miller-Rabin primality test for 32-bit numbers
bool is_prime(int p) {
    if (p < 2) return false;
    if (p == 2 || p == 3) return true;
    if (p % 2 == 0) return false;
    int d = p - 1, s = 0;
    while (d % 2 == 0) {
        d /= 2;
        ++s;
    }
    // Deterministic bases for 32-bit integers
    int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int a : bases) {
        if (a >= p) break;
        long long x = 1, pw = d;
        long long base = a;
        int mod = p;
        // x = base^pw % mod
        while (pw) {
            if (pw & 1) x = (x * base) % mod;
            base = (base * base) % mod;
            pw >>= 1;
        }
        if (x == 1 || x == p - 1) continue;
        bool ok = false;
        for (int r = 1; r < s; ++r) {
            x = (x * x) % mod;
            if (x == p - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 20000, "T");
    inf.readEoln();

    int cnt_large = 0;
    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int n = inf.readInt(1, 35, "n");
        inf.readSpace();
        long long m = inf.readLong(1LL, 1000000000000000000LL, "m");
        inf.readSpace();
        int p = inf.readInt(2, 1073741824, "p"); // 2 <= p <= 2^30
        inf.readEoln();

        // Check p is prime
        ensuref(is_prime(p), "p is not prime at test case %d: p = %d", tc + 1, p);

        // Count large cases
        if (n > 5 || m > 1000000000LL) ++cnt_large;
    }
    ensuref(cnt_large <= 1000, "Too many large cases: %d (>1000)", cnt_large);

    inf.readEof();
}

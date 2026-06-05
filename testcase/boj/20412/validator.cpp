#include "testlib.h"

using namespace std;

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

bool is_prime(int n) {
    if (n < 2) {
        return false;
    }
    if (n % 2 == 0) {
        return n == 2;
    }
    for (int d = 3; (long long)d * d <= n; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 1000000000, "m");
    inf.readSpace();
    int seed = inf.readInt(1, m - 1, "Seed");
    inf.readSpace();
    int x1 = inf.readInt(1, m - 1, "X_1");
    inf.readSpace();
    int x2 = inf.readInt(1, m - 1, "X_2");
    inf.readEoln();
    inf.readEof();

    ensuref(is_prime(m), "m must be prime: %d", m);

    bool possible = false;
    if (seed == x1) {
        possible = (x2 == x1);
    } else {
        long long numerator = (x2 - x1 + (long long)m) % m;
        long long denominator = (x1 - seed + (long long)m) % m;
        long long a = numerator * mod_pow(denominator, m - 2, m) % m;
        long long c = (x1 - a * seed % m + m) % m;
        possible = ((a * seed + c) % m == x1 && (a * x1 + c) % m == x2);
    }
    ensuref(possible, "there must exist 0 <= a, c < m generating X_1 and X_2");
}

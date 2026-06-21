#include "testlib.h"

#include <algorithm>
#include <vector>

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

long long normalize(long long value, long long mod) {
    value %= mod;
    if (value < 0) {
        value += mod;
    }
    return value;
}

int firstNonResidue(int p) {
    for (int x = 2; x < p; ++x) {
        if (modPow(x, (p - 1) / 2, p) == p - 1) {
            return x;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {
        3, 5, 7, 11, 13, 17, 29, 79, 101, 1009, 10007, 99991,
        1000003, 999983, 10000019, 99999989, 999999937
    };

    int scenarios = rnd.next(6, 24);
    vector<pair<int, int>> cases;
    cases.reserve(scenarios);

    for (int i = 0; i < scenarios; ++i) {
        int p = rnd.any(primes);
        int mode = rnd.next(0, 7);
        long long a;

        if (mode == 0) {
            long long x = rnd.next(1, min(p - 1, 10000));
            a = x * x % p;
        } else if (mode == 1) {
            int nonResidue = firstNonResidue(p);
            long long x = rnd.next(1, min(p - 1, 10000));
            a = nonResidue * (x * x % p) % p;
        } else if (mode == 2) {
            a = -rnd.next(1, 1000000000);
        } else if (mode == 3) {
            a = rnd.any(vector<int>{-1000000000, -999999999, 999999999, 1000000000});
        } else if (mode == 4) {
            a = rnd.next(1, p - 1);
            if (rnd.next(2) == 0) {
                a -= p;
            }
        } else if (mode == 5) {
            a = rnd.any(vector<int>{1, -1, 2, -2, p - 1, 1 - p});
        } else {
            a = rnd.next(-1000000000, 1000000000);
        }

        while (normalize(a, p) == 0) {
            a = rnd.next(-1000000000, 1000000000);
        }
        cases.push_back({(int)a, p});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [a, p] : cases) {
        println(a, p);
    }

    return 0;
}

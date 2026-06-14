#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000000000LL;

int divisorCount(int64 n) {
    int result = 1;
    for (int64 p = 2; p * p <= n; ++p) {
        if (n % p != 0) continue;
        int exponent = 0;
        while (n % p == 0) {
            n /= p;
            ++exponent;
        }
        result *= exponent + 1;
    }
    if (n > 1) result *= 2;
    return result;
}

bool boundedPower(int64 base, int exponent, int64& value) {
    __int128 current = 1;
    for (int i = 0; i < exponent; ++i) {
        current *= base;
        if (current > LIMIT) return false;
    }
    value = static_cast<int64>(current);
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int64 x = 1;

    if (mode <= 2) {
        int64 n = rnd.next(1, mode == 0 ? 2000 : 1000000);
        int64 candidate;
        while (!boundedPower(n, divisorCount(n), candidate)) {
            n = rnd.next(1, 1000000);
        }
        x = candidate;
    } else if (mode == 3) {
        vector<int64> bases = {2, 3, 4, 5, 6, 8, 10, 12, 16, 20, 25, 36, 64, 100};
        int64 base = rnd.any(bases);
        int exponent = rnd.next(2, 60);
        while (!boundedPower(base, exponent, x)) {
            exponent = rnd.next(2, 60);
        }
    } else if (mode == 4) {
        vector<int64> edges = {
            1,
            LIMIT,
            LIMIT - rnd.next(0, 1000000),
            1000000000000000000LL / rnd.next(1, 1000)
        };
        x = rnd.any(edges);
    } else {
        x = rnd.next(1LL, LIMIT);
    }

    println(x);
    return 0;
}

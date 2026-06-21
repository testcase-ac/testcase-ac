#include "testlib.h"

#include <algorithm>
#include <limits>

using namespace std;

const __int128_t LIMIT = numeric_limits<long long>::max();

__int128_t multiplyCapped(__int128_t a, long long b) {
    __int128_t product = static_cast<__int128_t>(a) * b;
    if (product > LIMIT) {
        return LIMIT + 1ULL;
    }
    return product;
}

__int128_t binomCapped(int n, int k) {
    k = min(k, n - k);
    __int128_t result = 1;
    for (int i = 1; i <= k; ++i) {
        __int128_t next = static_cast<__int128_t>(result) * (n - i + 1) / i;
        if (next > LIMIT) {
            return LIMIT + 1ULL;
        }
        result = next;
    }
    return result;
}

bool fitsSigned64(int p, int r, int c) {
    __int128_t value = binomCapped(r, c);
    if (value > LIMIT) {
        return false;
    }

    for (int i = 0; i < r - c; ++i) {
        value = multiplyCapped(value, p);
        if (value > LIMIT) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 1000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        setTestCase(i);

        int caseNumber = inf.readInt(-2147483647, 2147483647, "caseNumber");
        inf.readSpace();
        int p = inf.readInt(1, 100000, "P");
        inf.readSpace();
        int r = inf.readInt(0, 100000, "R");
        inf.readSpace();
        int c = inf.readInt(0, r, "C");
        inf.readEoln();

        ensuref(fitsSigned64(p, r, c),
                "requested entry overflows signed 64-bit integer in case %d: P=%d R=%d C=%d",
                caseNumber, p, r, c);
    }

    inf.readEof();
}

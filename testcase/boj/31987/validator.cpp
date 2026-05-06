#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Q: number of queries
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // We will also check the implicit statement constraint:
    // 1 <= i <= j <= j*k < 2^31
    // Using 64-bit for safety.
    const int64 LIM = (1LL << 31) - 1; // j * k <= LIM

    for (int qi = 0; qi < Q; ++qi) {
        int64 i = inf.readLong(1LL, LIM, "i");
        inf.readSpace();
        int64 j = inf.readLong(1LL, LIM, "j");
        inf.readSpace();
        int64 k = inf.readLong(1LL, LIM, "k");
        inf.readEoln();

        ensuref(i <= j,
                "Query %d: must satisfy i <= j, but got i=%lld, j=%lld",
                qi + 1, (long long)i, (long long)j);

        // Check j * k < 2^31
        // Use 128-bit to avoid overflow.
        i128 prod = (i128)j * (i128)k;
        ensuref(prod < (i128)(1LL << 31),
                "Query %d: must satisfy j * k < 2^31, but got j=%lld, k=%lld, j*k=%lld",
                qi + 1, (long long)j, (long long)k, (long long)prod);
    }

    inf.readEof();
}

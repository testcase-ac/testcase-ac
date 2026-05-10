#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check it's a power of two between 1 (2^0) and 2^10.
    int N = inf.readInt(1, 1<<10, "N");
    ensuref((N & (N - 1)) == 0, "N is not a power of 2: %d", N);
    inf.readEoln();

    // Read the N x N distinct non-negative integers < 2^31.
    const long long MAXV = (1LL<<31) - 1;
    vector<long long> vals;
    vals.reserve((long long)N * N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char nameBuf[32];
            snprintf(nameBuf, sizeof(nameBuf), "a_%d_%d", i, j);
            long long x = inf.readLong(0LL, MAXV, nameBuf);
            vals.push_back(x);
            if (j + 1 < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Ensure we read exactly N*N values.
    ensuref((long long)vals.size() == (long long)N * N,
            "Read %d values but expected %d", (int)vals.size(), N * N);

    // Check all values are distinct.
    sort(vals.begin(), vals.end());
    for (int i = 1; i < (int)vals.size(); i++) {
        ensuref(vals[i] != vals[i-1],
                "Duplicate value detected: %lld appears more than once", vals[i]);
    }

    inf.readEof();
    return 0;
}

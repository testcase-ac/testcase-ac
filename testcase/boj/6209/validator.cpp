#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate first line: d, n, m
    long long d = inf.readLong(1LL, 1000000000LL, "d");
    inf.readSpace();
    int n = inf.readInt(0, 50000, "n");
    inf.readSpace();
    int m = inf.readInt(0, n, "m");
    inf.readEoln();

    // If there are any islands, d must be at least 2 to allow positions in [1, d-1]
    if (n > 0) {
        ensuref(d >= 2,
                "Invalid input: n = %d > 0 requires d >= 2, but d = %lld", n, d);
    }

    // Read positions of the n islands
    vector<long long> pos;
    pos.reserve(n);
    for (int i = 0; i < n; i++) {
        long long x = inf.readLong(1LL, d - 1, "pos_i");
        inf.readEoln();
        pos.push_back(x);
    }

    // Check all positions are distinct
    sort(pos.begin(), pos.end());
    for (int i = 1; i < n; i++) {
        ensuref(pos[i] != pos[i-1],
                "Duplicate island position detected: %lld appears at least twice",
                pos[i]);
    }

    // No extra data
    inf.readEof();
    return 0;
}

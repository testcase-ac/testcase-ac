#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Read grid and collect all heights
    vector<long long> vals;
    vals.reserve((long long)n * m);
    for (int i = 0; i < n; i++) {
        vector<long long> row = inf.readLongs(m, 0LL, 1000000000LL, "h");
        inf.readEoln();
        for (long long x : row) {
            vals.push_back(x);
        }
    }

    // Check all heights are distinct
    sort(vals.begin(), vals.end());
    for (size_t i = 1; i < vals.size(); i++) {
        ensuref(vals[i] != vals[i-1],
                "Duplicate height detected: %lld appears more than once", vals[i]);
    }

    // No extra data
    inf.readEof();
    return 0;
}

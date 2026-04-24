#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n and m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 5000, "m");
    inf.readEoln();

    // Second line: array a of length n
    vector<long long> a = inf.readLongs(n, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    // Check distinctness of array elements
    {
        // We can use an unordered_set for speed
        unordered_set<long long> seen;
        seen.reserve(n * 2);
        for (int idx = 0; idx < n; idx++) {
            long long v = a[idx];
            ensuref(!seen.count(v),
                    "Duplicate array element at position %d: %lld", idx + 1, v);
            seen.insert(v);
        }
    }

    // Next m lines: queries
    for (int qi = 0; qi < m; qi++) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readSpace();
        // k <= n worst case, will check tighter bound below
        int k = inf.readInt(1, n, "k");
        inf.readEoln();

        ensuref(i <= j,
                "In query %d: i must be <= j, but got i=%d, j=%d",
                qi + 1, i, j);
        int len = j - i + 1;
        ensuref(k >= 1 && k <= len,
                "In query %d: k=%d is out of valid range [1, %d]",
                qi + 1, k, len);
    }

    // No extra data
    inf.readEof();
    return 0;
}

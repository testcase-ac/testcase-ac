#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    // Read permutation
    vector<int> a = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    // Check that a is a permutation of 1..n
    vector<bool> seen(n + 1, false); // 1-based
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        ensuref(!seen[val], "Duplicate value %d found at position %d", val, i + 1);
        seen[val] = true;
    }
    for (int v = 1; v <= n; ++v) {
        ensuref(seen[v], "Value %d missing from permutation", v);
    }

    inf.readEof();
}

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 40000, "n");
    inf.readEoln();

    // Read permutation of length n
    vector<int> a = inf.readInts(n, 1, n, "a");
    inf.readEoln();

    // Check that it's a permutation: all values 1..n appear exactly once
    vector<char> seen(n+1, 0);
    for (int i = 0; i < n; i++) {
        int v = a[i];
        ensuref(!seen[v],
                "Duplicate port mapping detected at position %d: value %d appears more than once",
                i+1, v);
        seen[v] = 1;
    }
    // (Since each a[i] is in [1,n] by readInts, and there are n of them, this ensures a permutation.)

    inf.readEof();
    return 0;
}

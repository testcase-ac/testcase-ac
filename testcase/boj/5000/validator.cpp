#include "testlib.h"
#include <vector>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    // Read the initial permutation
    vector<int> a = inf.readInts(n, 1, n, "initial_permutation");
    inf.readEoln();

    // Read the target permutation
    vector<int> b = inf.readInts(n, 1, n, "target_permutation");
    inf.readEoln();

    // Check that 'a' is a permutation of [1..n]
    vector<char> seen(n+1, 0);
    for (int i = 0; i < n; i++) {
        int v = a[i];
        ensuref(!seen[v], "Duplicate element in initial_permutation: %d", v);
        seen[v] = 1;
    }
    // Reset and check 'b'
    memset(seen.data(), 0, seen.size());
    for (int i = 0; i < n; i++) {
        int v = b[i];
        ensuref(!seen[v], "Duplicate element in target_permutation: %d", v);
        seen[v] = 1;
    }

    // All input consumed
    inf.readEof();
    return 0;
}

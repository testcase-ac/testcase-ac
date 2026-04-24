#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    // Read permutation a
    vector<int> a = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    // Read permutation b
    vector<int> b = inf.readInts(n, 1, n, "b_i");
    inf.readEoln();

    // Check that a is a permutation
    vector<char> seen(n+1, 0);
    for (int i = 0; i < n; i++) {
        int v = a[i];
        ensuref(!seen[v], "Value %d appears multiple times in array a at position %d", v, i+1);
        seen[v] = 1;
    }
    // Reset and check b
    fill(seen.begin(), seen.end(), 0);
    for (int i = 0; i < n; i++) {
        int v = b[i];
        ensuref(!seen[v], "Value %d appears multiple times in array b at position %d", v, i+1);
        seen[v] = 1;
    }

    inf.readEof();
    return 0;
}

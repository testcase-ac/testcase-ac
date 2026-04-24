#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of children
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // Read the permutation of size n
    vector<int> p = inf.readInts(n, 1, n, "p_i");
    inf.readEoln();

    // Check that it's a valid permutation: no duplicates
    vector<char> seen(n+1, 0);
    for (int i = 0; i < n; i++) {
        int x = p[i];
        ensuref(!seen[x],
                "Duplicate number %d found at position %d",
                x, i+1);
        seen[x] = 1;
    }

    // No extra data
    inf.readEof();
    return 0;
}

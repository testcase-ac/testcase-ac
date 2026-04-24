#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    vector<char> seen(n+1);
    vector<int> perm(n);

    // Read three permutations
    for (int t = 1; t <= 3; t++) {
        // Read one line of permutation
        for (int i = 0; i < n; i++) {
            // Read the i-th number in the t-th line
            perm[i] = inf.readInt(1, n, "perm");
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
        // Check for duplicates / missing values
        // Reset seen array
        memset(seen.data(), 0, n+1);
        for (int i = 0; i < n; i++) {
            int x = perm[i];
            ensuref(!seen[x],
                    "Duplicate value in line %d at position %d: %d",
                    t, i+1, x);
            seen[x] = 1;
        }
        // Optionally, we could check that all values appear by
        // ensuring after this loop that sum of seen[1..n] == n,
        // but since each readInt is within [1,n] and we checked no duplicates,
        // the set must be exactly {1..n}.
    }

    inf.readEof();
    return 0;
}

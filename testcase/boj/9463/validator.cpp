#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Set the current test case for clearer error messages
        setTestCase(tc);

        // Read n
        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();

        // Read first permutation
        vector<int> p1 = inf.readInts(n, 1, n, "perm1");
        inf.readEoln();
        // Validate it's a permutation: check duplicates
        {
            vector<char> seen(n+1, 0);
            for (int i = 0; i < n; i++) {
                int x = p1[i];
                ensuref(!seen[x],
                        "Duplicate value %d in first permutation at position %d (test case %d)",
                        x, i+1, tc);
                seen[x] = 1;
            }
        }

        // Read second permutation
        vector<int> p2 = inf.readInts(n, 1, n, "perm2");
        inf.readEoln();
        // Validate it's a permutation: check duplicates
        {
            vector<char> seen(n+1, 0);
            for (int i = 0; i < n; i++) {
                int x = p2[i];
                ensuref(!seen[x],
                        "Duplicate value %d in second permutation at position %d (test case %d)",
                        x, i+1, tc);
                seen[x] = 1;
            }
        }
    }

    // No extra characters after last test case
    inf.readEof();
    return 0;
}

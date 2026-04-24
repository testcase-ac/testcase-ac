#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read n
        int n = inf.readInt(4, 5000, "n");
        inf.readEoln();

        // Read the sequence A of length n
        vector<int> A = inf.readInts(n, 1, 10000, "A");
        inf.readEoln();

        // Check all A[i] are distinct
        vector<bool> seen(10001, false);
        for (int i = 0; i < n; i++) {
            int x = A[i];
            ensuref(!seen[x],
                    "Duplicate value in test case %d at position %d: %d",
                    tc, i+1, x);
            seen[x] = true;
        }
    }

    inf.readEof();
    return 0;
}

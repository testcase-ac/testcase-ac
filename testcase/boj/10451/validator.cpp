#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N
        int N = inf.readInt(2, 1000, "N");
        inf.readEoln();

        // Read the permutation of size N
        vector<int> perm = inf.readInts(N, 1, N, "pi");
        inf.readEoln();

        // Check that it's a valid permutation: no duplicates
        vector<char> seen(N+1, false);
        for (int i = 0; i < N; i++) {
            int v = perm[i];
            ensuref(!seen[v],
                    "Duplicate value %d in permutation at test case %d position %d",
                    v, tc, i+1);
            seen[v] = true;
        }
    }

    inf.readEof();
    return 0;
}

#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    long long total_N = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // 2. Read N
        int N = inf.readInt(1, 1000000, "N");
        inf.readEoln();

        total_N += N;
        ensuref(total_N <= 1000000, "Sum of N over all testcases exceeds 1_000_000 (at testcase %d)", tc);

        // 3. Read S
        string S = inf.readToken("[HT]{1,1000000}", "S");
        ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d) at testcase %d", (int)S.size(), N, tc);
        inf.readEoln();

        // 4. Validate S only contains 'H' or 'T' (already done by regex), and length checked above.

        // 5. No further global properties to check (the problem does not guarantee that the answer always exists).
        //    So we do not need to check for "always possible" or simulate the process.
    }

    inf.readEof();
}

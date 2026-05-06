#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    set<int> seen_N; // To check for duplicate N if needed (not required by statement, so not used)

    for (int tc = 1; tc <= T; ++tc) {
        // 2. Read N
        int N = inf.readInt(7, 1000000, "N");
        inf.readEoln();

        // 3. Check N is odd
        ensuref(N % 2 == 1, "N at test case %d is not odd: N = %d", tc, N);

        // 4. Check N > 5 (already ensured by lower bound 7 in readInt)
        // 5. Check N <= 1,000,000 (already ensured by upper bound in readInt)
    }

    inf.readEof();
}

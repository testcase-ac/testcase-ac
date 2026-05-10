#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // 2. Read p and n
        int p = inf.readInt(1, 1000000, "p");
        inf.readSpace();
        int n = inf.readInt(2, 100, "n");
        inf.readEoln();

        // 3. Read a_i
        std::vector<int> a = inf.readInts(n, 1, 1000000, "a_i");
        inf.readEoln();

        // 4. No further global constraints in the statement.
        //    Do NOT check sum(a_i) >= p, since the statement allows "IMPOSSIBLE" outputs.
        //    Only check per-value constraints (already enforced by readInts).
    }

    inf.readEof();
}

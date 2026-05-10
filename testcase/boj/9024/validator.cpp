#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read t
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int test = 0; test < t; ++test) {
        setTestCase(test + 1);

        // 2. Read n and K
        int n = inf.readInt(2, 1000000, "n");
        inf.readSpace();
        int K = inf.readInt(-100000000, 100000000, "K");
        inf.readEoln();

        // 3. Read n integers, check range and uniqueness
        vector<int> S = inf.readInts(n, -100000000, 100000000, "S_i");
        inf.readEoln();

        set<int> seen;
        for (int i = 0; i < n; ++i) {
            int x = S[i];
            ensuref(seen.count(x) == 0, "Duplicate value %d found at index %d in test case %d", x, i + 1, test + 1);
            seen.insert(x);
        }
    }

    inf.readEof();
}

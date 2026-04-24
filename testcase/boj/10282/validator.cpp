#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read n, d, c
        int n = inf.readInt(1, 10000, "n");
        inf.readSpace();
        int d = inf.readInt(1, 100000, "d");
        inf.readSpace();
        int c = inf.readInt(1, n, "c");
        inf.readEoln();

        // Track seen dependencies to prevent duplicates
        set<pair<int,int>> deps;
        deps.clear();

        for (int i = 0; i < d; i++) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readSpace();
            int s = inf.readInt(0, 1000, "s");
            inf.readEoln();

            // No self-dependency
            ensuref(a != b,
                    "Loop detected at dependency index %d in test case %d: (%d -> %d)",
                    i, tc, a, b);

            // No duplicate dependency (a, b)
            pair<int,int> p = make_pair(a, b);
            ensuref(deps.count(p) == 0,
                    "Multiple dependencies detected at dependency index %d in test case %d: (%d -> %d)",
                    i, tc, a, b);
            deps.insert(p);
        }
    }

    inf.readEof();
    return 0;
}

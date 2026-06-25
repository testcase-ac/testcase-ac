#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int caseIndex = 1; caseIndex <= 100000; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(0, 2000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 1999000, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            inf.readEof();
            return 0;
        }

        ensuref(2 <= n && n <= 2000, "n must be in [2, 2000], got %d", n);

        int maxEdges = n * (n - 1) / 2;
        ensuref(2 <= m && m <= maxEdges,
                "m must be in [2, n(n-1)/2], got m=%d for n=%d", m, n);

        set<pair<int, int>> roads;
        for (int i = 1; i <= m; ++i) {
            int v = inf.readInt(1, n, "v");
            inf.readSpace();
            int w = inf.readInt(1, n, "w");
            inf.readSpace();
            int p = inf.readInt(1, 2, "p");
            inf.readEoln();

            ensuref(v != w, "road %d has equal endpoints %d", i, v);

            pair<int, int> road = minmax(v, w);
            ensuref(roads.insert(road).second,
                    "multiple roads connect intersections %d and %d", v, w);
            (void)p;
        }
    }

    // CHECK: The statement gives no test-case count, so this uses the local
    // default cap for terminator-based multi-case input.
    ensuref(false, "too many test cases without terminating 0 0 line");
}

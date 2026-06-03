#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 5000, "N");
        inf.readSpace();

        long long maxEdges = 1LL * n * (n - 1) / 2;
        int m = inf.readInt(1, (int)min(1000000LL, maxEdges), "M");
        inf.readEoln();

        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int x = inf.readInt(1, n, "x");
            inf.readSpace();
            int y = inf.readInt(x + 1, n, "y");
            inf.readEoln();

            ensuref(edges.insert({x, y}).second,
                    "duplicate alliance in test case %d at edge %d: (%d, %d)",
                    tc, i, x, y);
        }
    }

    inf.readEof();
}

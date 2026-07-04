#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    ensuref(!inf.eof(), "input must contain at least one test case");

    int testCase = 0;
    while (!inf.eof()) {
        ++testCase;
        setTestCase(testCase);

        int n = inf.readInt(0, 10000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 20000, "m");
        inf.readEoln();

        long long maxSimpleEdges = 1LL * n * (n - 1) / 2;
        ensuref(m <= maxSimpleEdges,
                "m=%d exceeds the maximum number of simple edges for n=%d", m, n);

        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int x = inf.readInt(1, n, "x");
            inf.readSpace();
            int y = inf.readInt(1, n, "y");
            inf.readEoln();

            ensuref(x != y, "self-loop at edge %d: (%d, %d)", i, x, y);
            if (x > y) {
                swap(x, y);
            }
            ensuref(edges.insert({x, y}).second,
                    "duplicate edge at edge %d: (%d, %d)", i, x, y);
        }
    }

    inf.readEof();
}

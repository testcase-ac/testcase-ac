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

        int n = inf.readInt(2, 2500, "N");
        inf.readSpace();
        int m = inf.readInt(1, 10000, "M");
        inf.readEoln();

        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(1, n, "B");
            inf.readEoln();

            // CHECK: the statement forbids repeated directed edges, but does not forbid self-loops.
            ensuref(edges.insert({a, b}).second,
                    "repeated directed edge in testcase %d at edge %d: (%d, %d)",
                    tc, i, a, b);
        }
    }

    inf.readEof();
}

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

        int n = inf.readInt(1, 10000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 10000, "m");
        inf.readSpace();
        int k = inf.readInt(1, 100000, "k");
        inf.readEoln();

        set<pair<int, int>> edges;
        for (int i = 1; i <= k; ++i) {
            int x = inf.readInt(1, n, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, m, "y_i");
            inf.readEoln();

            // CHECK: The statement defines E as an edge set, so repeated
            // endpoint pairs are rejected even though the input paragraph does
            // not separately state that the listed edges are distinct.
            ensuref(edges.emplace(x, y).second,
                    "duplicate edge at index %d: (%d, %d)", i, x, y);
        }
    }

    inf.readEof();
}

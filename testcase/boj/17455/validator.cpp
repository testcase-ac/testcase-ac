#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    string labels = inf.readToken("[KDH]{2,200000}", "C");
    ensuref(static_cast<int>(labels.size()) == n,
            "label string length must be N: expected %d, got %d",
            n,
            static_cast<int>(labels.size()));
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "U");
        inf.readSpace();
        int v = inf.readInt(1, n, "V");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: (%d, %d)", i + 1, u, v);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: (%d, %d)",
                i + 1,
                u,
                v);
    }

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static vector<int> readDistinctVertices(int p, int n, const char* name) {
    vector<int> seen(n + 1, 0);
    vector<int> values;
    values.reserve(p);

    for (int i = 0; i < p; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int v = inf.readInt(1, n, name);
        ensuref(!seen[v], "%s contains duplicate vertex %d", name, v);
        seen[v] = 1;
        values.push_back(v);
    }
    inf.readEoln();

    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int maxM = static_cast<int>(min(1LL * n * (n - 1), 200000LL));
    int m = inf.readInt(0, maxM, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge index %d: (%d, %d)", i + 1, u, v);
        ensuref(edges.insert({u, v}).second,
                "duplicate edge at edge index %d: (%d, %d)", i + 1, u, v);
    }

    int p = inf.readInt(0, n, "p");
    inf.readEoln();

    readDistinctVertices(p, n, "a_i");
    readDistinctVertices(p, n, "b_i");

    inf.readEof();
}

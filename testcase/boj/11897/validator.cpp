#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read V, E
    int V = inf.readInt(5, 700, "V");
    inf.readSpace();
    int E = inf.readInt(1, 123456, "E");
    inf.readEoln();

    // 2. Read E edges
    set<pair<int, int>> edge_set;
    vector<pair<int, int>> edges(E + 1); // 1-based indexing for edge numbers

    for (int i = 1; i <= E; ++i) {
        int u = inf.readInt(1, V, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, V, "v_i");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i, u, v);

        int a = min(u, v);
        int b = max(u, v);
        ensuref(!edge_set.count({a, b}), "Multiple edge detected between %d and %d at edge %d", a, b, i);
        edge_set.insert({a, b});
        edges[i] = {u, v};
    }

    // 3. Read Q
    int Q = inf.readInt(1, 50000, "Q");
    inf.readEoln();

    // 4. Read Q queries
    for (int i = 0; i < Q; ++i) {
        int l = inf.readInt(1, E, "l");
        inf.readSpace();
        int r = inf.readInt(l, E, "r"); // l <= r <= E
        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int findRoot(vector<int>& parent, int v) {
    if (parent[v] == v) return v;
    return parent[v] = findRoot(parent, parent[v]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    set<pair<int, int>> edges;
    int components = n;

    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge index %d: (%d, %d)", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i, a, b);

        int ra = findRoot(parent, a);
        int rb = findRoot(parent, b);
        if (ra != rb) {
            parent[rb] = ra;
            --components;
        }
    }

    ensuref(components == 1, "graph is not connected");
    inf.readEof();
}

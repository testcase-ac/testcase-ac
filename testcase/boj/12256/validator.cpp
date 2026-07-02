#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(2, 15, "N");
        inf.readEoln();

        Dsu dsu(n);
        set<pair<int, int>> edges;
        for (int i = 1; i <= n - 1; ++i) {
            int x = inf.readInt(1, n, "X_i");
            inf.readSpace();
            int y = inf.readInt(1, n, "Y_i");
            inf.readEoln();

            ensuref(x != y, "self-loop in case %d edge %d: %d", caseIndex, i, x);
            pair<int, int> edge = minmax(x, y);
            ensuref(edges.insert(edge).second,
                    "duplicate edge in case %d edge %d: %d %d", caseIndex, i, x, y);
            ensuref(dsu.unite(x, y),
                    "cycle in case %d edge %d: %d %d", caseIndex, i, x, y);
        }

        int root = dsu.find(1);
        for (int v = 2; v <= n; ++v) {
            ensuref(dsu.find(v) == root, "case %d is not connected at node %d", caseIndex, v);
        }
    }

    inf.readEof();
}

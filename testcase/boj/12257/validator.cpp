#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
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

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 1000, "N");
        inf.readEoln();

        Dsu dsu(n);
        set<pair<int, int>> edges;
        for (int i = 1; i <= n - 1; ++i) {
            int x = inf.readInt(1, n, "X_i");
            inf.readSpace();
            int y = inf.readInt(1, n, "Y_i");
            inf.readEoln();

            ensuref(x != y, "self-loop in test case %d at edge %d: %d", tc, i, x);
            auto edge = minmax(x, y);
            ensuref(edges.insert(edge).second,
                    "duplicate edge in test case %d at edge %d: %d %d", tc, i, x, y);
            ensuref(dsu.unite(x, y),
                    "cycle in test case %d at edge %d: %d %d", tc, i, x, y);
        }

        int root = dsu.find(1);
        for (int v = 2; v <= n; ++v) {
            ensuref(dsu.find(v) == root,
                    "test case %d is not connected: vertex %d is disconnected", tc, v);
        }
    }

    inf.readEof();
}

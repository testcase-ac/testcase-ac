#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500, "N");
    inf.readSpace();
    int maxM = min(50000, n * (n - 1) / 2);
    int m = inf.readInt(n - 1, maxM, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    Dsu dsu(n);
    for (int i = 1; i <= m; ++i) {
        int s = inf.readInt(1, n - 1, "S_i");
        inf.readSpace();
        int d = inf.readInt(s + 1, n, "D_i");
        inf.readSpace();
        inf.readInt(1, 10000, "C_i");
        inf.readEoln();

        ensuref(edges.insert({s, d}).second,
                "duplicate bridge endpoints at edge %d: %d %d", i, s, d);
        dsu.unite(s, d);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "candidate bridge graph is disconnected");
    }

    inf.readEof();
}

#include "testlib.h"

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
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement gives several official file sizes but no formal T bound.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int commonN = -1;
    long long totalVertices = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();
        if (commonN == -1) {
            commonN = n;
        } else {
            ensuref(n == commonN,
                    "test case %d has n=%d, expected the file-wide n=%d",
                    tc, n, commonN);
        }

        totalVertices += n;
        // CHECK: no total input-size bound is stated; cap scalar volume for local validation.
        ensuref(totalVertices <= 5000000LL,
                "total vertices exceed local practical cap: %lld", totalVertices);

        Dsu dsu(n);
        set<pair<int, int>> edges;
        for (int i = 1; i <= n - 1; ++i) {
            int u = inf.readInt(1, n, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, n, "v_i");
            inf.readEoln();

            ensuref(u != v, "loop at edge %d: (%d, %d)", i, u, v);
            auto edge = minmax(u, v);
            ensuref(edges.insert(edge).second,
                    "duplicate edge at edge %d: (%d, %d)", i, u, v);
            ensuref(dsu.unite(u, v), "cycle closes at edge %d: (%d, %d)", i, u, v);
        }

        int root = dsu.find(1);
        for (int v = 2; v <= n; ++v) {
            ensuref(dsu.find(v) == root, "vertex %d is disconnected", v);
        }
    }

    inf.readEof();
}

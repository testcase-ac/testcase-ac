#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int commonN = -1;
    long long totalVertices = 0;

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();

        if (tc == 1) {
            commonN = n;
        } else {
            ensuref(n == commonN,
                    "all trees in a single file must have the same n, expected %d but found %d",
                    commonN, n);
        }

        totalVertices += n;
        // CHECK: The statement describes official files up to n=100000 but gives no T cap.
        // Cap total vertices to keep generated repository inputs practically sized.
        ensuref(totalVertices <= 200000, "total vertices across test cases exceed 200000");

        Dsu dsu(n);
        set<pair<int, int>> edges;

        for (int i = 1; i <= n - 1; ++i) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readEoln();

            ensuref(u != v, "loop at edge %d: (%d, %d)", i, u, v);

            auto edge = minmax(u, v);
            ensuref(edges.insert(edge).second, "duplicate edge at edge %d: (%d, %d)", i, u, v);
            ensuref(dsu.unite(u, v), "cycle formed at edge %d: (%d, %d)", i, u, v);
        }

        ensuref((int)edges.size() == n - 1, "tree must contain exactly n - 1 edges");
    }

    inf.readEof();
}

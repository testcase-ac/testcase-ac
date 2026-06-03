#include "testlib.h"

#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) {
            return;
        }
        if (rank[ra] < rank[rb]) {
            parent[ra] = rb;
        } else if (rank[ra] > rank[rb]) {
            parent[rb] = ra;
        } else {
            parent[rb] = ra;
            ++rank[ra];
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 5, "K");
    inf.readEoln();

    ensuref(n > k, "N must be greater than K so at least one non-market town exists");

    vector<int> seenMarket(n + 1, 0);
    for (int i = 1; i <= k; ++i) {
        int market = inf.readInt(1, n, "market");
        inf.readEoln();
        ensuref(!seenMarket[market], "duplicate market town %d at market index %d", market, i);
        seenMarket[market] = 1;
    }

    DSU dsu(n);
    for (int edge = 1; edge <= m; ++edge) {
        int a = inf.readInt(1, n, "i");
        inf.readSpace();
        int b = inf.readInt(1, n, "j");
        inf.readSpace();
        inf.readInt(1, 1000, "L");
        inf.readEoln();

        // CHECK: The statement gives only endpoint bounds and does not forbid loops or parallel roads.
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int town = 2; town <= n; ++town) {
        ensuref(dsu.find(town) == root, "town %d is not reachable from town 1", town);
    }

    inf.readEof();
}

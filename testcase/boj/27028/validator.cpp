#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 40000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 39999, "M");
    inf.readEoln();

    // CHECK: Distance Queries asks for distances along the path between farms,
    // so the road network is validated as one connected tree.
    ensuref(m == n - 1, "road count must form a tree: N=%d, M=%d", n, m);

    Dsu dsu(n);
    for (int i = 1; i <= m; ++i) {
        int f1 = inf.readInt(1, n, "F1");
        inf.readSpace();
        int f2 = inf.readInt(1, n, "F2");
        inf.readSpace();
        int length = inf.readInt(1, 1000, "L");
        inf.readSpace();
        string direction = inf.readToken("[NESW]", "D");
        inf.readEoln();

        ensuref(f1 != f2, "road %d is a self-loop at farm %d", i, f1);
        ensuref(dsu.unite(f1, f2), "road %d creates a cycle: %d %d", i, f1, f2);
        (void)length;
        (void)direction;
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "farm %d is disconnected from farm 1", i);
    }

    int k = inf.readInt(1, 10000, "K");
    inf.readEoln();
    for (int i = 1; i <= k; ++i) {
        inf.readInt(1, n, "query_farm_1");
        inf.readSpace();
        inf.readInt(1, n, "query_farm_2");
        inf.readEoln();
    }

    inf.readEof();
}

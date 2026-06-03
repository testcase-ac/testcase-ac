#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

struct DisjointSet {
    vector<int> parent;

    explicit DisjointSet(int n) : parent(n + 1) {
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
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    DisjointSet dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d", i, a);
        ensuref(dsu.unite(a, b), "cycle or duplicate edge at edge %d: (%d, %d)", i, a, b);
    }

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    bool hasTypeTwo = false;
    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 2, "t_i");
        inf.readSpace();

        if (t == 1) {
            int u = inf.readInt(1, n, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, n, "v_i");
            inf.readEoln();

            ensuref(u != v, "type 1 query %d has equal endpoints: %d", i, u);
        } else {
            inf.readInt(1, n, "x_i");
            inf.readEoln();
            hasTypeTwo = true;
        }
    }

    ensuref(hasTypeTwo, "at least one type 2 query is required");
    inf.readEof();
}

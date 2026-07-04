#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

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
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: N=1 is written in the bounds, but the required first query uses the
    // maximum edge weight of an N-1 edge tree, which is undefined for N=1.
    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    Dsu dsu(n);
    long long maxWeight = 0;
    for (int i = 1; i <= n - 1; ++i) {
        // CHECK: the limit block says vertices are at most N-1, but the prose
        // defines N cities and the official sample uses vertex N.
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        long long w = inf.readLong(1LL, 1000000000LL, "w_i");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at city %d", i, u);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle between %d and %d", i, u, v);
        maxWeight = max(maxWeight, w);
    }

    for (int j = 1; j <= q; ++j) {
        long long l = inf.readLong(1LL, 1000000000LL, "l_j");
        inf.readSpace();
        long long r = inf.readLong(l, 1000000000LL, "r_j");
        inf.readEoln();

        if (j == 1) {
            ensuref(l == 1, "first query lower bound must be 1, found %lld", l);
            ensuref(r == maxWeight,
                    "first query upper bound must be maximum edge weight %lld, found %lld",
                    maxWeight,
                    r);
        }
    }

    inf.readEof();
}

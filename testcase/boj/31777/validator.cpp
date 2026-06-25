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

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 300000, "N");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 300000, "sum of N exceeds 300000");

        Dsu dsu(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u = inf.readInt(1, n, "u_i");
            inf.readSpace();
            int v = inf.readInt(u + 1, n, "v_i");
            inf.readSpace();
            inf.readLong(1LL, 1000000000LL, "w_i");
            inf.readEoln();

            ensuref(dsu.unite(u, v), "edge %d creates a cycle: %d %d", i, u, v);
        }
    }

    inf.readEof();
}

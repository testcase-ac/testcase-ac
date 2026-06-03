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
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;
        if (size[ra] < size[rb]) swap(ra, rb);
        parent[rb] = ra;
        size[ra] += size[rb];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    __int128 total = 0;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) inf.readSpace();
        long long h = inf.readLong(1LL, 1000000000LL, "h_j");
        total += h;
    }
    inf.readEoln();

    ensuref(total % n == 0, "total hay must be divisible by N");

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge index %d: (%d, %d)", i, u, v);
        ensuref(dsu.unite(u, v), "cycle or duplicate edge at edge index %d: (%d, %d)", i, u, v);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "barn %d is disconnected from barn 1", v);
    }

    inf.readEof();
}

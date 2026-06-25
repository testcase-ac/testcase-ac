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

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    // CHECK: the statement says "fourth line", but samples and token order show this line immediately after n and m.
    vector<int> black = inf.readInts(n, 0, 1, "p_i");
    inf.readEoln();

    int black_count = 0;
    for (int color : black) {
        black_count += color;
    }
    ensuref(black_count >= m, "number of black vertices is %d, less than m=%d", black_count, m);

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int u = inf.readInt(1, n, "u_i");
        inf.readEoln();

        ensuref(v != u, "self-loop at edge %d: %d", i, v);
        pair<int, int> edge = minmax(v, u);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, v, u);
        ensuref(dsu.unite(v, u), "cycle formed at edge %d: %d %d", i, v, u);
    }

    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(dsu.find(vertex) == dsu.find(1), "graph is not connected at vertex %d", vertex);
    }

    inf.readEof();
}

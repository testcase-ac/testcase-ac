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
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
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

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    // CHECK: The statement gives only M <= 100000. Allow M = 0 for the
    // single-city connected graph.
    int m = inf.readInt(0, 100000, "m");
    inf.readSpace();
    // CHECK: The statement gives only K <= 10000. Allow an empty route list
    // because the format and output remain well-defined.
    int k = inf.readInt(0, 10000, "k");
    inf.readEoln();

    Dsu dsu(n);
    for (int edge = 1; edge <= m; ++edge) {
        int a = inf.readInt(1, n, "edge_u");
        inf.readSpace();
        int b = inf.readInt(1, n, "edge_v");
        inf.readSpace();
        // CHECK: The statement only writes w <= 200, but canal widths are
        // positive and the task searches positive boat widths.
        int w = inf.readInt(1, 200, "width");
        inf.readEoln();

        // CHECK: The statement does not forbid loops or parallel canals.
        (void)w;
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int city = 2; city <= n; ++city) {
        ensuref(dsu.find(city) == root, "city %d is not connected to city 1", city);
    }

    for (int route = 1; route <= k; ++route) {
        int a = inf.readInt(1, n, "route_u");
        inf.readSpace();
        int b = inf.readInt(1, n, "route_v");
        inf.readEoln();

        // CHECK: The statement does not require the two route endpoints to be distinct.
        (void)a;
        (void)b;
    }

    inf.readEof();
}

#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    int n, comp;
    vector<int> p, r;
    DSU(int _n): n(_n), comp(_n), p(_n+1), r(_n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x;
        if (r[x] == r[y]) r[x]++;
        comp--;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N and M
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    DSU dsu(N);

    // Read edges
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000, "C_i");
        inf.readEoln();

        // Union for connectivity check (self-loops don't affect comp)
        if (a != b) {
            dsu.unite(a, b);
        }
    }

    // Check global connectivity
    ensuref(dsu.comp == 1, "Graph is not connected: %d components found", dsu.comp);

    inf.readEof();
    return 0;
}

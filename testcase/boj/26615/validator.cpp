#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n), size(n, 1) {
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

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "M");
    inf.readSpace();
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long cells = 1LL * n * m;
    ensuref(cells <= 100000, "N * M must be at most 100000, got %lld", cells);

    Dsu dsu(static_cast<int>(cells));
    int openEdges = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            int wall = inf.readInt(0, 1, "A_i_j");
            if (j + 1 < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            if (wall == 0) {
                ++openEdges;
                int u = i * m + j;
                int v = (i + 1) * m + j;
                ensuref(dsu.unite(u, v), "vertical open edges create a cycle at A[%d][%d]", i, j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            int wall = inf.readInt(0, 1, "B_i_j");
            if (j + 1 < m - 1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            if (wall == 0) {
                ++openEdges;
                int u = i * m + j;
                int v = i * m + (j + 1);
                ensuref(dsu.unite(u, v), "horizontal open edges create a cycle at B[%d][%d]", i, j);
            }
        }
    }

    ensuref(openEdges == cells - 1, "maze must have exactly N * M - 1 open edges, got %d", openEdges);
    int root = dsu.find(0);
    for (int v = 1; v < cells; ++v) {
        ensuref(dsu.find(v) == root, "maze is disconnected at cell index %d", v);
    }

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();
    for (int i = 0; i < k; ++i) {
        int s = inf.readInt(1, t, "S_i");
        inf.readSpace();
        inf.readInt(s, t, "E_i");
        inf.readSpace();
        inf.readInt(0, n - 1, "a_i");
        inf.readSpace();
        inf.readInt(0, m - 1, "b_i");
        inf.readSpace();
        inf.readInt(0, n - 1, "c_i");
        inf.readSpace();
        inf.readInt(0, m - 1, "d_i");
        inf.readSpace();
        inf.readInt(1, 1000, "V_i");
        inf.readEoln();
    }

    inf.readEof();
}

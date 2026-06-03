#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

class DSU {
public:
    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
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
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 20000, "M");
    inf.readEoln();

    DSU dsu(n);
    for (int i = 1; i <= m; ++i) {
        int s = inf.readInt(1, n, "S");
        inf.readSpace();
        int e = inf.readInt(1, n, "E");
        inf.readSpace();
        inf.readInt(1, 100, "L");
        inf.readEoln();

        dsu.unite(s, e);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is disconnected: vertex %d is not connected to vertex 1", v);
    }

    inf.readEof();
}

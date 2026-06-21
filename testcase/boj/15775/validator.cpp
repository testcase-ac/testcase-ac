#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
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

    int n = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 250000, "M");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 0; i < m; ++i) {
        int s = inf.readInt(1, n, "s_i");
        inf.readSpace();
        int e = inf.readInt(1, n, "e_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000000, "w_i");
        inf.readEoln();

        (void)w;
        // CHECK: The statement does not forbid loops or parallel edges, and N=1, M=1 is within bounds.
        dsu.unite(s, e);
    }

    int root = dsu.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(dsu.find(vertex) == root,
                "graph is not connected: vertex %d is disconnected from vertex 1",
                vertex);
    }

    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    int previous = 0;
    for (int i = 0; i < k; ++i) {
        int a = inf.readInt(1, n, "a_i");
        ensuref(previous < a,
                "a_i must be strictly increasing: a_%d=%d after %d",
                i + 1,
                a,
                previous);
        previous = a;
        if (i + 1 < k) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}

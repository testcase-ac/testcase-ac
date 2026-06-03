#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n) {
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

    int p = inf.readInt(2, 1000, "p");
    inf.readSpace();
    int w = inf.readInt(1, 50000, "w");
    inf.readEoln();

    int c = inf.readInt(0, p - 1, "c");
    inf.readSpace();
    int v = inf.readInt(0, p - 1, "v");
    inf.readEoln();
    ensuref(c != v, "c and v must be different: %d", c);

    Dsu dsu(p);
    for (int i = 0; i < w; ++i) {
        int wStart = inf.readInt(0, p - 1, "w_start");
        inf.readSpace();
        int wEnd = inf.readInt(0, p - 1, "w_end");
        inf.readSpace();
        inf.readInt(1, 1000, "w_width");
        inf.readEoln();

        ensuref(wStart != wEnd, "road endpoints must be different at edge %d: %d", i + 1, wStart);
        dsu.unite(wStart, wEnd);
    }

    ensuref(dsu.find(c) == dsu.find(v), "there must be a path between c=%d and v=%d", c, v);

    inf.readEof();
}

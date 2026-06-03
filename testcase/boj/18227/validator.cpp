#include "testlib.h"

#include <vector>
using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
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

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int capital = inf.readInt(1, n, "C");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: %d", i, x);
        ensuref(dsu.unite(x, y), "edge %d creates a cycle: %d %d", i, x, y);
    }
    for (int city = 2; city <= n; ++city) {
        ensuref(dsu.find(1) == dsu.find(city), "tree is disconnected at city %d", city);
    }

    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        int a = inf.readInt(1, n, "A");
        inf.readEoln();
    }

    (void)capital;
    inf.readEof();
}

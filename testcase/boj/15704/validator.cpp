#include "testlib.h"

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

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(n - 1, 100000, "m");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    set<pair<int, int>> edges;
    Dsu dsu(n);
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n - 1, "a");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "b");
        inf.readSpace();
        int c = inf.readInt(1, 1000, "c");
        inf.readSpace();
        int t = inf.readInt(1, 1000, "t");
        inf.readEoln();

        ensuref(edges.insert({a, b}).second,
                "duplicate edge at index %d: (%d, %d)", i, a, b);
        dsu.unite(a, b);
        (void)c;
        (void)t;
    }

    ensuref(dsu.find(1) == dsu.find(n),
            "no path exists between intersections 1 and %d", n);

    inf.readEof();
}

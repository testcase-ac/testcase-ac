#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 500000, "M");
    inf.readEoln();

    vector<long long> x(n + 1), y(n + 1);
    set<pair<long long, long long>> points;
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; ++i) {
        x[i] = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        y[i] = inf.readLong(0LL, 1000000000LL, "y_i");
        inf.readEoln();

        ensuref(points.insert({x[i], y[i]}).second,
                "duplicate point at index %d: (%lld, %lld)", i, x[i], y[i]);
        parent[i] = i;
    }

    auto find_root = [&](int v) {
        while (parent[v] != v) {
            parent[v] = parent[parent[v]];
            v = parent[v];
        }
        return v;
    };
    auto unite = [&](int a, int b) {
        a = find_root(a);
        b = find_root(b);
        if (a != b) {
            parent[b] = a;
        }
    };

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, n, "w_i");
        inf.readSpace();
        string c = inf.readToken("[RGB]", "c_i");
        inf.readEoln();

        ensuref(v != w, "loop at edge index %d: (%d, %d)", i, v, w);
        ensuref(y[v] != y[w],
                "horizontal edge at index %d: (%d, %d) with y=%lld", i, v, w, y[v]);

        auto edge = minmax(v, w);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i, v, w);

        unite(v, w);
    }

    set<int> grounded_components;
    for (int i = 1; i <= n; ++i) {
        if (y[i] == 0) {
            grounded_components.insert(find_root(i));
        }
    }
    for (int i = 1; i <= n; ++i) {
        ensuref(grounded_components.count(find_root(i)) != 0,
                "point %d is not directly or indirectly connected to the ground", i);
    }

    inf.readEof();
}

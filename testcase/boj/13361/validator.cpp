#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    explicit DSU(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        while (v != parent[v]) {
            parent[v] = parent[parent[v]];
            v = parent[v];
        }
        return v;
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
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250000, "n");
    inf.readEoln();

    vector<pair<long long, long long>> rectangles;
    rectangles.reserve(n);
    vector<long long> values;
    values.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        long long s = inf.readLong(1LL, 1000000000LL, "s_i");
        inf.readSpace();
        long long t = inf.readLong(1LL, 1000000000LL, "t_i");
        inf.readEoln();

        ensuref(s <= t,
                "rectangle %d has s_i (%lld) greater than t_i (%lld)",
                i + 1, s, t);
        rectangles.push_back({s, t});
        values.push_back(s);
        values.push_back(t);
    }
    inf.readEof();

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    auto idOf = [&](long long value) {
        return int(lower_bound(values.begin(), values.end(), value) - values.begin());
    };

    DSU dsu(int(values.size()));
    vector<pair<int, int>> edges;
    edges.reserve(n);
    vector<int> singletonCount(values.size(), 0);

    for (auto [s, t] : rectangles) {
        int a = idOf(s);
        int b = idOf(t);
        if (a == b) {
            ++singletonCount[a];
        } else {
            dsu.unite(a, b);
            edges.push_back({a, b});
        }
    }

    vector<int> vertexCount(values.size(), 0);
    vector<int> edgeCount(values.size(), 0);
    vector<int> occupiedCount(values.size(), 0);

    for (int v = 0; v < int(values.size()); ++v) {
        int root = dsu.find(v);
        ++vertexCount[root];
        ensuref(singletonCount[v] <= 1,
                "width %lld is forced by %d square rectangles",
                values[v], singletonCount[v]);
        occupiedCount[root] += singletonCount[v];
    }

    for (auto [a, b] : edges) {
        ++edgeCount[dsu.find(a)];
    }

    for (int root = 0; root < int(values.size()); ++root) {
        if (dsu.find(root) != root) {
            continue;
        }
        ensuref(edgeCount[root] + occupiedCount[root] <= vertexCount[root],
                "component has %d rectangles but only %d available distinct widths",
                edgeCount[root] + occupiedCount[root], vertexCount[root]);
    }

    return 0;
}

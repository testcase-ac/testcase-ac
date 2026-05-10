#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, rnk;
    vector<bool> hasPlant;
    DSU(int n): n(n), p(n+1), rnk(n+1,0), hasPlant(n+1,false) {
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    // return false if union would merge two components that both already have plants
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return true;
        if (hasPlant[a] && hasPlant[b]) return false;
        if (rnk[a] < rnk[b]) swap(a,b);
        p[b] = a;
        if (rnk[a] == rnk[b]) ++rnk[a];
        hasPlant[a] = hasPlant[a] || hasPlant[b];
        return true;
    }
};

struct Edge {
    int u, v;
    int w;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 1000;
    const int M_MAX = 100000;

    int N = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(1, M_MAX, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // read K distinct plant cities in [1..N]
    vector<int> plant(K);
    set<int> plantSet;
    for (int i = 0; i < K; ++i) {
        plant[i] = inf.readInt(1, N, "plant_city");
        if (i + 1 < K) inf.readSpace();
        ensuref(!plantSet.count(plant[i]),
                "Plant city duplicated: %d", plant[i]);
        plantSet.insert(plant[i]);
    }
    inf.readEoln();

    // read M edges
    vector<Edge> edges;
    edges.reserve(M);
    set<pair<int,int>> edgeSet; // undirected uniqueness
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int w = inf.readInt(1, 10000, "w");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edgeSet.count({a,b}),
                "Multiple edges detected between %d and %d", a, b);
        edgeSet.insert({a,b});

        edges.push_back({u,v,w});
    }

    // Global property: it must be possible to supply electricity to all cities
    // under the constraint that each connected component has at most one plant.
    // We also ensure the "no two plants in same connected component" condition
    // is satisfiable for any chosen subset of edges: it is inherent in our
    // construction of the minimum-cost forest.

    // Check existence of feasible solution and that MST-like minimum cost
    // exists (i.e., graph+plants connect all nodes when merging only if
    // a component currently has no plant).
    DSU dsu(N);
    for (int c : plant) {
        dsu.hasPlant[ dsu.find(c) ] = true;
    }

    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b){ return a.w < b.w; });

    long long totalCost = 0;
    int componentsWithPower = 0;
    vector<bool> cityPowered(N+1, false);
    for (int c : plant) {
        if (!cityPowered[c]) {
            cityPowered[c] = true;
            ++componentsWithPower;
        }
    }

    for (const auto &e : edges) {
        int ru = dsu.find(e.u);
        int rv = dsu.find(e.v);
        if (ru == rv) continue;
        bool plantU = dsu.hasPlant[ru];
        bool plantV = dsu.hasPlant[rv];

        // if both components already have plants, we cannot connect them
        if (plantU && plantV) continue;

        bool ok = dsu.unite(ru, rv);
        ensuref(ok, "Internal DSU consistency error");
        totalCost += e.w;

        int r = dsu.find(ru);
        // mark all cities in combined component as "potentially powerable"
        // but for feasibility, it's enough to track that every city belongs
        // to some component that either has or can get a plant. Since plants
        // are fixed and we never merge two-plant components, if the graph
        // is such that some city cannot reach a plant without merging
        // two-plant components, then after full Kruskal run it will remain
        // isolated from any plant.

        // We just run Kruskal; no need to explicitly mark cities here.
    }

    // After Kruskal, verify that for every city, some path to at least one plant exists
    // under the "at most one plant per component" constraint.
    // Build mapping from DSU component to whether it has a plant.
    vector<bool> compHasPlant(N+1, false);
    for (int i = 1; i <= N; ++i) {
        int r = dsu.find(i);
        compHasPlant[r] = compHasPlant[r] || plantSet.count(i);
    }
    for (int i = 1; i <= N; ++i) {
        int r = dsu.find(i);
        ensuref(compHasPlant[r],
                "City %d cannot be supplied with electricity under constraints", i);
    }

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Graph {
    int n = 0;
    set<pair<int, int>> edges;
};

void addEdge(Graph& g, int u, int v) {
    if (u > v) swap(u, v);
    g.edges.insert({u, v});
}

void addPath(Graph& g, const vector<int>& path) {
    for (int i = 1; i < (int)path.size(); ++i) {
        addEdge(g, path[i - 1], path[i]);
    }
}

void addBamboo(Graph& g, int len, bool attachLeaves) {
    int first = g.n + 1;
    vector<int> spine;
    for (int i = 0; i <= len; ++i) {
        spine.push_back(first + i);
    }
    g.n += len + 1;
    addPath(g, spine);

    if (!attachLeaves) return;
    for (int v : spine) {
        if (rnd.next(2) == 0) continue;
        int a = ++g.n;
        int b = ++g.n;
        addEdge(g, v, a);
        addEdge(g, v, b);
    }
}

Graph makeValidForest() {
    Graph g;
    int components = rnd.next(1, 3);
    for (int i = 0; i < components; ++i) {
        int len = rnd.next(3, 8);
        addBamboo(g, len, true);
    }
    return g;
}

Graph makeShortPath() {
    Graph g;
    int len = rnd.next(1, 2);
    g.n = len + 1;
    vector<int> path;
    for (int i = 1; i <= g.n; ++i) path.push_back(i);
    addPath(g, path);
    return g;
}

Graph makeBadLeafCount(int leaves) {
    Graph g;
    int len = rnd.next(3, 7);
    int hub = rnd.next(1, len + 1);
    vector<int> spine;
    for (int i = 1; i <= len + 1; ++i) spine.push_back(i);
    g.n = len + 1;
    addPath(g, spine);
    for (int i = 0; i < leaves; ++i) {
        addEdge(g, hub, ++g.n);
    }
    return g;
}

Graph makeDepthTwoBranch() {
    Graph g;
    int len = rnd.next(3, 7);
    int hub = rnd.next(1, len + 1);
    vector<int> spine;
    for (int i = 1; i <= len + 1; ++i) spine.push_back(i);
    g.n = len + 1;
    addPath(g, spine);
    int a = ++g.n;
    int b = ++g.n;
    addEdge(g, hub, a);
    addEdge(g, a, b);
    return g;
}

Graph makeCycle() {
    Graph g;
    g.n = rnd.next(4, 10);
    for (int i = 1; i <= g.n; ++i) {
        addEdge(g, i, i == g.n ? 1 : i + 1);
    }
    return g;
}

Graph makeMixedForest() {
    Graph g = makeValidForest();
    int offset = g.n;
    int len = rnd.next(1, 2);
    g.n += len + 1;
    for (int i = 1; i <= len; ++i) {
        addEdge(g, offset + i, offset + i + 1);
    }
    return g;
}

Graph makeDenseSmall() {
    Graph g;
    g.n = rnd.next(5, 12);
    vector<pair<int, int>> candidates;
    for (int i = 1; i <= g.n; ++i) {
        for (int j = i + 1; j <= g.n; ++j) {
            candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    int m = rnd.next(g.n, min<int>((int)candidates.size(), 25));
    for (int i = 0; i < m; ++i) {
        addEdge(g, candidates[i].first, candidates[i].second);
    }
    return g;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    Graph g;
    if (mode == 0) {
        g = makeValidForest();
    } else if (mode == 1) {
        g = makeShortPath();
    } else if (mode == 2) {
        g = makeBadLeafCount(rnd.any(vector<int>{1, 3, 4}));
    } else if (mode == 3) {
        g = makeDepthTwoBranch();
    } else if (mode == 4) {
        g = makeCycle();
    } else if (mode == 5) {
        g = makeMixedForest();
    } else {
        g = makeDenseSmall();
    }

    vector<pair<int, int>> edges(g.edges.begin(), g.edges.end());
    shuffle(edges.begin(), edges.end());
    println(g.n, (int)edges.size());
    for (auto [u, v] : edges) {
        if (rnd.next(2)) swap(u, v);
        println(u, v);
    }

    return 0;
}

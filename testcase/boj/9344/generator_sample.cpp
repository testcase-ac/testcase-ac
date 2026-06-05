#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

pair<int, int> normEdge(int u, int v) {
    if (u > v) swap(u, v);
    return {u, v};
}

void orientRandomly(Edge& edge) {
    if (rnd.next(2)) swap(edge.u, edge.v);
}

vector<int> shuffledLabels(int n) {
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());
    return label;
}

int randomBetween(int lo, int hi) {
    if (hi < lo) return lo;
    return rnd.next(lo, hi);
}

vector<Edge> makeTree(int n, int firstWeight) {
    vector<int> label = shuffledLabels(n);
    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        int u = label[i];
        int v = label[rnd.next(i)];
        edges.push_back({u, v, firstWeight + i - 1});
    }
    return edges;
}

void addExtraEdges(vector<Edge>& edges, int n, int targetM, int nextWeight, const set<pair<int, int>>& protectedEdges) {
    set<pair<int, int>> used;
    for (const Edge& edge : edges) used.insert(normEdge(edge.u, edge.v));

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            pair<int, int> e = {u, v};
            if (!used.count(e) && !protectedEdges.count(e)) candidates.push_back(e);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    while ((int)edges.size() < targetM && !candidates.empty()) {
        auto [u, v] = candidates.back();
        candidates.pop_back();
        edges.push_back({u, v, nextWeight++});
    }
}

vector<Edge> makeCase(int mode, int& n, int& p, int& q) {
    n = rnd.next(2, 12);
    vector<Edge> edges;
    set<pair<int, int>> protectedEdges;

    if (mode == 0) {
        n = 2;
        p = 1;
        q = 2;
        edges.push_back({1, 2, rnd.next(1, 400000)});
    } else if (mode == 1) {
        edges = makeTree(n, rnd.next(1, 30));
        Edge query = rnd.any(edges);
        p = query.u;
        q = query.v;
        int maxM = n * (n - 1) / 2;
        int targetM = randomBetween(n - 1, min(maxM, n + 4));
        addExtraEdges(edges, n, targetM, 1000 + rnd.next(2000), protectedEdges);
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        p = 1;
        q = n;
        int maxM = n * (n - 1) / 2;
        edges = makeTree(n, 1);
        pair<int, int> query = normEdge(p, q);
        edges.erase(remove_if(edges.begin(), edges.end(), [&](const Edge& edge) {
                        return normEdge(edge.u, edge.v) == query;
                    }),
                    edges.end());
        protectedEdges.insert(query);
        addExtraEdges(edges, n, min(n + rnd.next(1, 4), maxM - 1), 100, protectedEdges);
        edges.push_back({p, q, 300000 + rnd.next(1000)});
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        p = rnd.next(1, n);
        do {
            q = rnd.next(1, n);
        } while (q == p);
        int maxM = n * (n - 1) / 2;
        edges.push_back({p, q, 1});
        vector<Edge> tree = makeTree(n, 2);
        for (const Edge& edge : tree) {
            if (normEdge(edge.u, edge.v) != normEdge(p, q)) edges.push_back(edge);
        }
        addExtraEdges(edges, n, randomBetween(n - 1, min(maxM, n + 6)), 1000, protectedEdges);
    } else {
        n = rnd.next(5, 12);
        p = rnd.next(1, n);
        do {
            q = rnd.next(1, n);
        } while (q == p);
        int maxM = n * (n - 1) / 2;
        edges = makeTree(n, rnd.next(10, 80));
        pair<int, int> query = normEdge(p, q);
        bool hasQuery = false;
        for (Edge& edge : edges) {
            if (normEdge(edge.u, edge.v) == query) {
                hasQuery = true;
                edge.w = rnd.next(1, 400);
            }
        }
        if (!hasQuery) edges.push_back({p, q, rnd.next(1, 400)});
        addExtraEdges(edges, n, randomBetween(n, min(maxM, n + 8)), 1000 + rnd.next(5000), protectedEdges);
    }

    set<int> seenWeights;
    for (Edge& edge : edges) {
        while (seenWeights.count(edge.w)) ++edge.w;
        seenWeights.insert(edge.w);
        orientRandomly(edge);
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = 10;
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n, p, q;
        vector<Edge> edges = makeCase(tc % 5, n, p, q);
        println(n, (int)edges.size(), p, q);
        for (const Edge& edge : edges) {
            println(edge.u, edge.v, edge.w);
        }
    }

    return 0;
}

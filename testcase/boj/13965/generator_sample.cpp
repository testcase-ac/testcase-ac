#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int duration;
};

static int edgeDuration(const vector<Edge>& edges, int u, int v) {
    if (u > v) swap(u, v);
    for (const Edge& edge : edges) {
        if (edge.u == u && edge.v == v) return edge.duration;
    }
    return -1;
}

static vector<vector<int>> buildAdj(int n, const vector<Edge>& edges) {
    vector<vector<int>> adj(n + 1);
    for (const Edge& edge : edges) {
        adj[edge.u].push_back(edge.v);
        adj[edge.v].push_back(edge.u);
    }
    return adj;
}

static vector<int> makeWalk(const vector<vector<int>>& adj, int steps) {
    int current = rnd.next(1, (int)adj.size() - 1);
    vector<int> path = {current};
    for (int i = 0; i < steps; ++i) {
        const vector<int>& nexts = adj[current];
        current = rnd.any(nexts);
        path.push_back(current);
    }
    return path;
}

static int loggedDuration(const vector<Edge>& edges, const vector<int>& path) {
    int total = 0;
    for (int i = 0; i + 1 < (int)path.size(); ++i) {
        total += edgeDuration(edges, path[i], path[i + 1]);
    }
    return total % 13;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int alice = rnd.next(1, n);
    int rabbit = rnd.next(1, n);
    while (rabbit == alice) rabbit = rnd.next(1, n);

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());

    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        int u = labels[i];
        int v = labels[rnd.next(0, i - 1)];
        if (u > v) swap(u, v);
        edges.push_back({u, v, rnd.next(1, 12)});
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (edgeDuration(edges, u, v) == -1) candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraEdges = rnd.next(0, min((int)candidates.size(), n));
    for (int i = 0; i < extraEdges; ++i) {
        edges.push_back({candidates[i].first, candidates[i].second, rnd.next(1, 12)});
    }

    vector<vector<int>> adj = buildAdj(n, edges);
    int trips = rnd.next(n, min(30, n * 3 + 4));
    vector<vector<int>> paths;
    paths.reserve(trips);

    for (int i = 0; i < trips; ++i) {
        int steps;
        if (i < (int)edges.size()) {
            steps = 1;
            paths.push_back({edges[i].u, edges[i].v});
            continue;
        }
        if (rnd.next(4) == 0) {
            steps = rnd.next(8, 24);
        } else {
            steps = rnd.next(1, 7);
        }
        paths.push_back(makeWalk(adj, steps));
    }

    shuffle(paths.begin(), paths.end());

    println(n, alice, rabbit, trips);
    for (const vector<int>& path : paths) {
        vector<int> line;
        line.push_back(loggedDuration(edges, path));
        line.push_back((int)path.size());
        line.insert(line.end(), path.begin(), path.end());
        println(line);
    }

    return 0;
}

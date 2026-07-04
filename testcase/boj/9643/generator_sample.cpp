#include "testlib.h"

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

vector<vector<int>> distancesFromGraph(int n, const vector<Edge>& edges) {
    vector<vector<pair<int, int>>> adj(n);
    for (const Edge& edge : edges) {
        adj[edge.u].push_back({edge.v, edge.w});
        adj[edge.v].push_back({edge.u, edge.w});
    }

    vector<vector<int>> d(n, vector<int>(n, 1000000000));
    for (int start = 0; start < n; ++start) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        d[start][start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();
            if (dist != d[start][u]) {
                continue;
            }
            for (auto [v, w] : adj[u]) {
                if (d[start][v] > dist + w) {
                    d[start][v] = dist + w;
                    pq.push({d[start][v], v});
                }
            }
        }
    }
    return d;
}

vector<Edge> makeTwoCityCase() {
    int w = rnd.next(1, 1000000);
    return {{0, 1, w}, {0, 1, rnd.next(w, 1000000)}};
}

vector<Edge> makeUnicyclicCase(int n) {
    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = i;
    }
    shuffle(vertices.begin(), vertices.end());

    int cycleSize = rnd.next(3, n);
    vector<Edge> edges;
    for (int i = 0; i < cycleSize; ++i) {
        int u = vertices[i];
        int v = vertices[(i + 1) % cycleSize];
        edges.push_back({u, v, rnd.next(1, 30)});
    }

    vector<int> attached(vertices.begin(), vertices.begin() + cycleSize);
    for (int i = cycleSize; i < n; ++i) {
        int u = vertices[i];
        int v = rnd.any(attached);
        edges.push_back({u, v, rnd.next(1, 30)});
        attached.push_back(u);
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCaseCount = rnd.next(1, 4);
    for (int tc = 0; tc < testCaseCount; ++tc) {
        int n;
        vector<Edge> edges;
        if (rnd.next(0, 9) == 0) {
            n = 2;
            edges = makeTwoCityCase();
        } else {
            n = rnd.next(3, 9);
            edges = makeUnicyclicCase(n);
        }

        vector<vector<int>> d = distancesFromGraph(n, edges);
        println(n);
        for (int i = 0; i < n; ++i) {
            println(d[i]);
        }
    }

    return 0;
}

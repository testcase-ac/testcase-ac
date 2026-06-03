#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int to;
    long long weight;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, min(n * (n - 1), 5000), "M");
    inf.readEoln();

    vector<vector<Edge>> graph(n);
    set<pair<int, int>> seenEdges;

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        long long w = inf.readLong(1LL, 1000000000LL, "w_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d -> %d", i, u, v);
        ensuref(seenEdges.insert({u, v}).second,
                "duplicate directed edge at edge %d: %d -> %d", i, u, v);

        graph[u - 1].push_back({v - 1, w});
    }

    const long long infDist = 4'000'000'000'000'000'000LL;

    for (int source = 0; source < n; ++source) {
        vector<long long> dist(n, infDist);
        vector<int> ways(n, 0);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<pair<long long, int>>>
            pq;

        dist[source] = 0;
        ways[source] = 1;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [currentDist, u] = pq.top();
            pq.pop();
            if (currentDist != dist[u]) {
                continue;
            }

            for (const Edge& edge : graph[u]) {
                long long nextDist = currentDist + edge.weight;
                if (nextDist < dist[edge.to]) {
                    dist[edge.to] = nextDist;
                    ways[edge.to] = ways[u];
                    pq.push({nextDist, edge.to});
                } else if (nextDist == dist[edge.to]) {
                    ways[edge.to] = min(2, ways[edge.to] + ways[u]);
                }
            }
        }

        for (int target = 0; target < n; ++target) {
            if (source == target || dist[target] == infDist) {
                continue;
            }
            ensuref(ways[target] == 1,
                    "shortest path from %d to %d is not unique", source + 1,
                    target + 1);
        }
    }

    inf.readEof();
}

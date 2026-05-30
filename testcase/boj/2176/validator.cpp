#include "testlib.h"
#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> edge_set;
    vector<vector<pair<int, int>>> graph(N + 1);

    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readSpace();
        int C = inf.readInt(1, 10000, "C");
        inf.readEoln();

        ensuref(A != B, "Self-loop detected at edge %d: (%d, %d)", i + 1, A, B);

        int u = min(A, B), v = max(A, B);
        ensuref(!edge_set.count({u, v}), "Multiple edge detected between %d and %d", u, v);
        edge_set.insert({u, v});

        graph[A].push_back({B, C});
        graph[B].push_back({A, C});
    }

    const long long INF = (1LL << 60);
    vector<long long> dist(N + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[2] = 0;
    pq.push({0, 2});
    while (!pq.empty()) {
        auto [du, u] = pq.top();
        pq.pop();
        if (du != dist[u]) {
            continue;
        }
        for (auto [v, w] : graph[u]) {
            if (dist[v] > du + w) {
                dist[v] = du + w;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> order(N);
    for (int i = 0; i < N; ++i) {
        order[i] = i + 1;
    }
    sort(order.begin(), order.end(), [&](int a, int b) {
        return dist[a] < dist[b];
    });

    const long long ANSWER_LIMIT = 2147483647LL;
    vector<long long> ways(N + 1);
    ways[2] = 1;
    for (int u : order) {
        if (u == 2 || dist[u] == INF) {
            continue;
        }
        for (auto [v, w] : graph[u]) {
            if (dist[v] < dist[u]) {
                ways[u] = min(ANSWER_LIMIT + 1, ways[u] + ways[v]);
            }
        }
    }
    ensuref(ways[1] <= ANSWER_LIMIT, "answer exceeds 2147483647: capped count is %lld", ways[1]);

    inf.readEof();
}

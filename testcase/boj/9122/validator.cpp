#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxN = 1000;
constexpr int kMaxM = 10000;
constexpr int kMaxL = 1000;
constexpr long long kInf = 4000000000000000000LL;
constexpr long long kAnswerCap = 1000000000LL;
constexpr long long kCountCap = kAnswerCap + 1;
constexpr int kMaxTotalSize = kMaxN + kMaxM;

struct Edge {
    int from;
    int to;
    int length;
};

vector<long long> shortestDistances(int n, const vector<vector<pair<int, int>>>& graph, int source) {
    vector<long long> dist(n + 1, kInf);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) {
            continue;
        }
        for (auto [to, length] : graph[v]) {
            long long nd = d + length;
            if (nd < dist[to]) {
                dist[to] = nd;
                pq.push({nd, to});
            }
        }
    }

    return dist;
}

long long addCapped(long long lhs, long long rhs) {
    return min(kCountCap, lhs + rhs);
}

long long countShortOrOneLongerRoutes(
    int n,
    const vector<Edge>& edges,
    const vector<long long>& dist,
    int s,
    int f
) {
    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = i + 1;
    }
    sort(vertices.begin(), vertices.end(), [&](int lhs, int rhs) {
        if (dist[lhs] != dist[rhs]) {
            return dist[lhs] > dist[rhs];
        }
        return lhs < rhs;
    });

    vector<long long> exact(n + 1, 0), plusOne(n + 1, 0);
    exact[f] = 1;

    for (int v : vertices) {
        if (dist[v] == kInf) {
            continue;
        }
        for (const Edge& edge : edges) {
            if (edge.from != v || dist[edge.to] == kInf) {
                continue;
            }
            if (dist[v] + edge.length == dist[edge.to]) {
                exact[v] = addCapped(exact[v], exact[edge.to]);
                plusOne[v] = addCapped(plusOne[v], plusOne[edge.to]);
            } else if (dist[v] + edge.length == dist[edge.to] + 1) {
                plusOne[v] = addCapped(plusOne[v], exact[edge.to]);
            }
        }
    }

    return addCapped(exact[s], plusOne[s]);
}

} // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for the number of cases.
    // Cap T so the total input remains practical while still allowing many cases.
    int testCases = inf.readInt(1, 100000, "T");
    inf.readEoln();
    int totalSize = 0;

    for (int tc = 1; tc <= testCases; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, kMaxN, "N");
        inf.readSpace();
        int m = inf.readInt(1, kMaxM, "M");
        inf.readEoln();
        totalSize += n + m;
        ensuref(totalSize <= kMaxTotalSize, "sum of N + M over test cases exceeds %d", kMaxTotalSize);

        vector<Edge> edges;
        edges.reserve(m);
        vector<vector<pair<int, int>>> graph(n + 1);

        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(1, n, "B");
            inf.readSpace();
            int length = inf.readInt(1, kMaxL, "L");
            inf.readEoln();

            ensuref(a != b, "road %d has equal endpoints: %d", i, a);

            edges.push_back({a, b, length});
            graph[a].push_back({b, length});
        }

        int s = inf.readInt(1, n, "S");
        inf.readSpace();
        int f = inf.readInt(1, n, "F");
        inf.readEoln();

        ensuref(s != f, "S and F must be different: %d", s);

        vector<long long> dist = shortestDistances(n, graph, s);
        ensuref(dist[f] != kInf, "there is no route from S=%d to F=%d", s, f);

        long long answer = countShortOrOneLongerRoutes(n, edges, dist, s, f);
        ensuref(answer <= kAnswerCap, "route count exceeds 1e9: %lld", answer);
    }

    inf.readEof();
}

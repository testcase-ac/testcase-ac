#include "testlib.h"

#include <algorithm>
#include <array>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int r = inf.readInt(1, 100000, "R");
    inf.readEoln();

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 1; i <= r; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readSpace();
        int d = inf.readInt(1, 5000, "D");
        inf.readEoln();

        // CHECK: the statement does not forbid loops or parallel roads.
        graph[a].push_back({b, d});
        graph[b].push_back({a, d});
    }
    inf.readEof();

    const long long infDist = numeric_limits<long long>::max() / 4;
    vector<array<long long, 2>> dist(n + 1, {infDist, infDist});
    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1][0] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (cost > dist[node][1]) {
            continue;
        }

        for (auto [next, weight] : graph[node]) {
            long long candidate = cost + weight;
            if (candidate < dist[next][0]) {
                dist[next][1] = dist[next][0];
                dist[next][0] = candidate;
                pq.push({candidate, next});
            } else if (dist[next][0] < candidate && candidate < dist[next][1]) {
                dist[next][1] = candidate;
                pq.push({candidate, next});
            }
        }
    }

    ensuref(dist[n][1] != infDist, "second-shortest path from 1 to N must exist");
}

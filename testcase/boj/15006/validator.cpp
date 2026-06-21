#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    vector<vector<pair<int, int>>> graph(n);
    set<pair<int, int>> seenEdges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n - 1, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "b_i");
        inf.readSpace();
        int d = inf.readInt(0, 500000, "d_i");
        inf.readEoln();

        ensuref(a != b, "loop at road index %d: (%d, %d)", i + 1, a, b);
        auto edge = minmax(a, b);
        ensuref(seenEdges.insert(edge).second,
                "duplicate road at index %d: (%d, %d)", i + 1, a, b);

        graph[a].push_back({b, d});
        graph[b].push_back({a, d});
    }
    inf.readEof();

    const long long infDist = (1LL << 62);
    vector<long long> dist(n, infDist);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [curDist, v] = pq.top();
        pq.pop();
        if (curDist != dist[v]) {
            continue;
        }
        for (auto [to, weight] : graph[v]) {
            if (dist[to] > curDist + weight) {
                dist[to] = curDist + weight;
                pq.push({dist[to], to});
            }
        }
    }

    for (int v = 0; v < n; ++v) {
        ensuref(dist[v] != infDist, "graph is not connected: vertex %d cannot reach 1", v);
    }

    vector<int> component(n, -1);
    vector<int> componentSize;
    vector<int> zeroEdgeCount;
    for (int start = 0; start < n; ++start) {
        if (component[start] != -1) {
            continue;
        }

        int id = int(componentSize.size());
        componentSize.push_back(0);
        zeroEdgeCount.push_back(0);
        vector<int> stack = {start};
        component[start] = id;

        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            ++componentSize[id];
            for (auto [to, weight] : graph[v]) {
                if (weight != 0 || dist[v] != dist[to]) {
                    continue;
                }
                ++zeroEdgeCount[id];
                if (component[to] == -1) {
                    component[to] = id;
                    stack.push_back(to);
                }
            }
        }
    }

    vector<int> terminalCount(componentSize.size(), 0);
    terminalCount[component[1]] = 1;
    for (int v = 0; v < n; ++v) {
        int id = component[v];
        for (auto [to, weight] : graph[v]) {
            if (component[to] == id) {
                continue;
            }
            if (dist[v] == dist[to] + weight) {
                ++terminalCount[id];
            }
        }
    }

    for (int id = 0; id < int(componentSize.size()); ++id) {
        ensuref(zeroEdgeCount[id] / 2 == componentSize[id] - 1,
                "zero-distance shortest-route component %d is not a tree", id);
        ensuref(terminalCount[id] == 1,
                "zero-distance shortest-route component %d has %d terminals", id,
                terminalCount[id]);
    }
}

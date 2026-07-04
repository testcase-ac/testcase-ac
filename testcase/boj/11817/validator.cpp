#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

void markConnected(const vector<vector<int>>& graph, vector<int>& visited) {
    vector<int> stack = {1};
    visited[1] = 1;

    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();

        for (int u : graph[v]) {
            if (!visited[u]) {
                visited[u] = 1;
                stack.push_back(u);
            }
        }
    }
}

bool containsBridge(const vector<vector<int>>& graph) {
    int n = static_cast<int>(graph.size()) - 1;
    vector<int> tin(n + 1, 0), low(n + 1, 0), parent(n + 1, 0), nextEdge(n + 1, 0);
    vector<int> stack = {1};
    int timer = 0;

    tin[1] = low[1] = ++timer;
    while (!stack.empty()) {
        int v = stack.back();

        if (nextEdge[v] < static_cast<int>(graph[v].size())) {
            int u = graph[v][nextEdge[v]++];
            if (u == parent[v]) {
                continue;
            }
            if (tin[u] == 0) {
                parent[u] = v;
                tin[u] = low[u] = ++timer;
                stack.push_back(u);
            } else {
                low[v] = min(low[v], tin[u]);
            }
            continue;
        }

        stack.pop_back();
        if (parent[v] != 0) {
            int p = parent[v];
            low[p] = min(low[p], low[v]);
            if (low[v] > tin[p]) {
                return true;
            }
        }
    }

    return false;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "M");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int length = inf.readInt(1, 1000, "length_i");
        inf.readEoln();

        ensuref(u != v, "pipe %d is a self-loop at station %d", i, u);
        // CHECK: "Some pairs" is interpreted as a simple graph, so parallel pipes are rejected.
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate pipe %d between stations %d and %d", i,
                edge.first, edge.second);
        (void)length;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int firstRobot = inf.readInt(1, n, "first_robot_station");
    inf.readSpace();
    int secondRobot = inf.readInt(1, n, "second_robot_station");
    inf.readEoln();
    (void)firstRobot;
    (void)secondRobot;

    vector<int> visited(n + 1, 0);
    markConnected(graph, visited);
    for (int i = 1; i <= n; ++i) {
        ensuref(visited[i], "system is not connected: station %d is unreachable", i);
    }

    ensuref(containsBridge(graph), "system must contain at least one magistral pipe");

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 15000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 30000, "M");
    inf.readEoln();

    vector<pair<int, int>> edges;
    vector<vector<int>> adj(n + 1);
    set<pair<int, int>> seen;

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge index %d: (%d, %d)", i, a, b);
        auto edge = minmax(a, b);
        ensuref(seen.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i, a, b);

        edges.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> is_center(n + 1, 0);
    int center_count = 0;
    for (int v = 1; v <= n; ++v) {
        int degree = static_cast<int>(adj[v].size());
        ensuref(degree > 0, "vertex %d is not in any sea urchin", v);
        if (degree >= 3) {
            is_center[v] = 1;
            ++center_count;
        } else {
            ensuref(degree <= 2, "spine vertex %d has invalid degree %d", v, degree);
        }
    }
    ensuref(center_count > 0, "there must be at least one sea urchin center");

    for (int i = 0; i < m; ++i) {
        int a = edges[i].first;
        int b = edges[i].second;
        ensuref(is_center[a] != is_center[b],
                "edge index %d does not connect exactly one center and one spine: (%d, %d)",
                i + 1, a, b);
    }

    vector<vector<int>> center_graph(n + 1);
    set<pair<int, int>> touching;
    for (int v = 1; v <= n; ++v) {
        if (is_center[v]) continue;

        if (adj[v].size() == 2) {
            int a = adj[v][0];
            int b = adj[v][1];
            ensuref(a != b, "spine vertex %d has duplicate center neighbors", v);
            auto edge = minmax(a, b);
            if (touching.insert(edge).second) {
                center_graph[a].push_back(b);
                center_graph[b].push_back(a);
            }
        }
    }

    vector<int> color(n + 1, -1);
    for (int start = 1; start <= n; ++start) {
        if (!is_center[start] || color[start] != -1) continue;

        vector<int> stack = {start};
        color[start] = 0;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int to : center_graph[v]) {
                if (color[to] == -1) {
                    color[to] = color[v] ^ 1;
                    stack.push_back(to);
                } else {
                    ensuref(color[to] != color[v],
                            "touching sea urchin centers %d and %d require the same sex",
                            v, to);
                }
            }
        }
    }

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(6, 50, "n");
    inf.readEoln();

    int m = n + 3;
    set<pair<int, int>> edgeSet;
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop", i + 1);
        int a = min(u, v);
        int b = max(u, v);
        ensuref(!edgeSet.count({a, b}), "edge %d duplicates %d %d", i + 1, a, b);
        edgeSet.insert({a, b});

        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> seen(n, 0);
    queue<int> q;
    seen[0] = 1;
    q.push(0);
    int reached = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++reached;
        for (int v : adj[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                q.push(v);
            }
        }
    }
    ensuref(reached == n, "graph is not connected");

    vector<int> cores;
    vector<int> isCore(n, 0);
    for (int i = 0; i < n; ++i) {
        if ((int)adj[i].size() != 2) {
            cores.push_back(i);
            isCore[i] = 1;
        }
    }
    ensuref((int)cores.size() == 6, "expected 6 core vertices, found %d", (int)cores.size());

    set<pair<int, int>> compressedEdges;
    for (int u : cores) {
        for (int v : adj[u]) {
            int prev = u;
            int cur = v;
            vector<int> walked(n, 0);
            while (!isCore[cur]) {
                ensuref((int)adj[cur].size() == 2, "normal vertex %d does not have degree 2", cur + 1);
                ensuref(!walked[cur], "path from core vertex %d does not reach another core", u + 1);
                walked[cur] = 1;

                int nxt = adj[cur][0] ^ adj[cur][1] ^ prev;
                prev = cur;
                cur = nxt;
            }

            int a = min(u, cur);
            int b = max(u, cur);
            compressedEdges.insert({a, b});
        }
    }
    ensuref((int)compressedEdges.size() == 9, "expected 9 paths between core vertices, found %d",
            (int)compressedEdges.size());

    const vector<pair<int, int>> rayEdges = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 4},
        {2, 3}, {2, 4}, {3, 4}, {4, 5},
    };

    sort(cores.begin(), cores.end());
    bool matchesRay = false;
    do {
        set<pair<int, int>> expected;
        for (auto [x, y] : rayEdges) {
            int a = min(cores[x], cores[y]);
            int b = max(cores[x], cores[y]);
            expected.insert({a, b});
        }
        if (expected == compressedEdges && cores[1] < cores[3]) {
            matchesRay = true;
            break;
        }
    } while (next_permutation(cores.begin(), cores.end()));

    ensuref(matchesRay, "compressed core graph is not a valid ray graph with B < D");

    inf.readEof();
}

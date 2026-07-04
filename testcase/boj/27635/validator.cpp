#include "testlib.h"

#include <algorithm>
#include <bitset>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int MAX_N = 1000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 1000, "m");
    inf.readEoln();

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: %d -> %d", i, x, y);
        ensuref(edges.insert({x, y}).second, "duplicate edge at edge %d: %d -> %d", i, x, y);
        adj[x].push_back(y);
        ++indegree[y];
    }

    queue<int> q;
    for (int v = 1; v <= n; ++v) {
        if (indegree[v] == 0) {
            q.push(v);
        }
    }

    vector<int> order;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int u : adj[v]) {
            if (--indegree[u] == 0) {
                q.push(u);
            }
        }
    }
    ensuref((int)order.size() == n, "graph must be acyclic");

    constexpr __int128 limit = ((__int128)1) << 80;
    vector<bitset<MAX_N + 1>> reaches(n + 1);
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int v = *it;
        for (int u : adj[v]) {
            reaches[v].set(u);
            reaches[v] |= reaches[u];
        }
    }

    vector<vector<int>> ancestors(n + 1);
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (reaches[u].test(v)) {
                ancestors[v].push_back(u);
            }
        }
    }

    vector<__int128> dp(n + 1, 0);

    for (int source = 1; source <= n; ++source) {
        fill(dp.begin(), dp.end(), 0);
        dp[source] = 1;

        for (int v : order) {
            if (v != source) {
                for (int u : ancestors[v]) {
                    dp[v] -= dp[u];
                    ensuref(-limit <= dp[v] && dp[v] <= limit,
                        "absolute tension exceeds 2^80 while processing source %d and vertex %d",
                        source, v);
                }
            }
        }

        for (int target = 1; target <= n; ++target) {
            ensuref(-limit <= dp[target] && dp[target] <= limit,
                    "absolute tension exceeds 2^80 for pair (%d, %d)", source, target);
        }
    }

    inf.readEof();
}

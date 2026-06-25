#include "testlib.h"

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "m");
    inf.readEoln();

    vector<vector<int>> adj(n + 1);
    unordered_set<long long> seen;
    seen.reserve(static_cast<size_t>(m) * 2 + 1);

    for (int edge = 1; edge <= m; ++edge) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readEoln();

        ensuref(i != j, "self conflict at edge %d: %d", edge, i);

        int a = min(i, j);
        int b = max(i, j);
        long long key = 1LL * a * (n + 1LL) + b;
        // CHECK: the statement describes m pairs of students who cannot work together,
        // so repeated listings of the same unordered pair are rejected.
        ensuref(seen.insert(key).second,
                "duplicate conflict pair at edge %d: (%d, %d)", edge, i, j);

        adj[i].push_back(j);
        adj[j].push_back(i);
    }

    vector<int> color(n + 1, -1);
    queue<int> q;
    for (int start = 1; start <= n; ++start) {
        if (color[start] != -1) {
            continue;
        }

        color[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else {
                    ensuref(color[v] != color[u],
                            "conflict graph is not bipartite at edge (%d, %d)", u, v);
                }
            }
        }
    }

    inf.readEof();
}

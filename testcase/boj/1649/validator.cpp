#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Prepare to detect multiple edges and self-loops
    vector< unordered_set<int> > seen(N+1);
    vector<pair<int,int>> edges;
    edges.reserve(M);

    // Read edges
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d -> %d)", i, u, v);
        auto &st = seen[u];
        auto res = st.insert(v);
        ensuref(res.second, "Multiple edges detected: (%d -> %d)", u, v);

        edges.emplace_back(u, v);
    }

    // Build adjacency and compute indegrees
    vector<vector<int>> adj(N+1);
    vector<int> indeg(N+1, 0);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        indeg[v]++;
    }

    // Check for cycles via Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    int visited = 0;
    vector<int> topo;
    topo.reserve(N);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        visited++;
        for (int v : adj[u]) {
            if (--indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    ensuref(visited == N, "The graph must be acyclic (DAG), but a cycle was found");
    vector<int> topoPos(N + 1);
    for (int i = 0; i < N; ++i) {
        topoPos[topo[i]] = i;
    }

    // Read A, B, K
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    // CHECK: the statement/generator use "A B K", but the official sample
    // places K on the next line.
    char beforeK = inf.readChar();
    ensuref(beforeK == ' ' || beforeK == '\n',
            "B and K must be separated by a space or newline");
    int K = inf.readInt(0, N-2, "K");
    inf.readEoln();
    ensuref(A != B, "A and B must be different: A=%d, B=%d", A, B);

    // Read intermediate nodes C_i
    vector<bool> used(N+1, false);
    vector<int> required;
    required.reserve(K);
    for (int i = 0; i < K; i++) {
        int c = inf.readInt(1, N, "C_i");
        ensuref(c != A && c != B,
                "Intermediate node C_%d must differ from A and B: C=%d, A=%d, B=%d",
                i, c, A, B);
        ensuref(!used[c],
                "Intermediate node C_%d = %d is repeated", i, c);
        used[c] = true;
        required.push_back(c);

        if (i + 1 < K) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();

    sort(required.begin(), required.end(), [&](int lhs, int rhs) {
        return topoPos[lhs] < topoPos[rhs];
    });

    const long long limit = 2000000000LL;
    const long long cap = limit + 1;
    long long totalPaths = 1;
    vector<long long> ways(N + 1);
    vector<int> checkpoints;
    checkpoints.reserve(K + 2);
    checkpoints.push_back(A);
    checkpoints.insert(checkpoints.end(), required.begin(), required.end());
    checkpoints.push_back(B);

    for (int i = 0; i + 1 < (int)checkpoints.size(); ++i) {
        int from = checkpoints[i];
        int to = checkpoints[i + 1];
        if (topoPos[from] >= topoPos[to]) {
            totalPaths = 0;
            break;
        }

        fill(ways.begin(), ways.end(), 0);
        ways[from] = 1;
        for (int node : topo) {
            if (topoPos[node] < topoPos[from] || topoPos[node] >= topoPos[to]) {
                continue;
            }
            if (ways[node] == 0) {
                continue;
            }
            for (int next : adj[node]) {
                if (topoPos[next] > topoPos[to]) {
                    continue;
                }
                ways[next] = min(cap, ways[next] + ways[node]);
            }
        }

        totalPaths = min(cap, totalPaths * ways[to]);
        if (totalPaths > limit) {
            break;
        }
        if (totalPaths == 0) {
            break;
        }
    }

    ensuref(totalPaths <= limit,
            "number of valid paths must not exceed 2000000000");
    return 0;
}

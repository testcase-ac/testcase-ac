#include "testlib.h"
#include <vector>
#include <array>
#include <queue>
#include <climits>
using namespace std;

// Dinic's algorithm for max flow
struct Dinic {
    struct Edge { int to, cap, rev; };
    int N;
    vector<vector<Edge>> G;
    vector<int> level, prog;
    Dinic(int n) : N(n), G(n), level(n), prog(n) {}
    void addEdge(int u, int v, int c) {
        G[u].push_back({v, c, (int)G[v].size()});
        G[v].push_back({u, 0, (int)G[u].size() - 1});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : G[u]) {
                if (level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }
    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int &i = prog[u]; i < (int)G[u].size(); ++i) {
            auto &e = G[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                int ret = dfs(e.to, t, min(f, e.cap));
                if (ret > 0) {
                    e.cap -= ret;
                    G[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(prog.begin(), prog.end(), 0);
            int pushed;
            while ((pushed = dfs(s, t, INT_MAX)) > 0) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int tc = 0;
    while (true) {
        ++tc;
        // no explicit limit on number of cases => assume ≤100000
        ensuref(tc <= 100000, "Too many test cases: %d", tc);
        // Read n, m (allow 0 for termination check)
        int n = inf.readInt(0, 140, "n");
        inf.readSpace();
        int m = inf.readInt(0, 70, "m");
        inf.readEoln();
        // Termination
        if (n == 0 && m == 0) break;
        // Validate ranges for real test cases
        ensuref(n >= 4, "n must be at least 4 at test case %d, found %d", tc, n);
        ensuref(m >= 1, "m must be at least 1 at test case %d, found %d", tc, m);
        // Read job capacities
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            p[i] = inf.readInt(1, 10, "p");
            inf.readEoln();
        }
        // Read students
        vector<int> year(m);
        vector<array<int,4>> choices(m);
        for (int i = 0; i < m; i++) {
            year[i] = inf.readInt(1, 3, "y");
            // Read 4 distinct choices
            vector<char> seen(n, 0);
            for (int k = 0; k < 4; k++) {
                inf.readSpace();
                int c = inf.readInt(0, n-1, "c");
                ensuref(!seen[c], "Duplicate choice %d for student %d in case %d", c, i, tc);
                seen[c] = 1;
                choices[i][k] = c;
            }
            inf.readEoln();
        }
        // Build flow network to check feasibility (every student must be assignable)
        // Nodes: source=0, students=1..m, jobs=m+1..m+n, sink=m+n+1
        int V = m + n + 2;
        int S = 0, T = V - 1;
        Dinic dinic(V);
        // Source -> students
        for (int i = 0; i < m; i++) {
            dinic.addEdge(S, 1 + i, 1);
            // Student -> his 4 chosen jobs
            for (int k = 0; k < 4; k++) {
                int job = choices[i][k];
                dinic.addEdge(1 + i, 1 + m + job, 1);
            }
        }
        // Jobs -> sink
        for (int j = 0; j < n; j++) {
            dinic.addEdge(1 + m + j, T, p[j]);
        }
        int flow = dinic.maxflow(S, T);
        ensuref(flow >= m,
                "No feasible assignment in test case %d: max flow %d < students %d",
                tc, flow, m);
    }
    inf.readEof();
    return 0;
}

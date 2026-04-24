#include "testlib.h"
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct Edge {
    int to, rev, cap;
};

struct Dinic {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;
    Dinic(int _n) : n(_n), adj(n), level(n), ptr(n) {}

    void addEdge(int u, int v, int c) {
        Edge a = {v, (int)adj[v].size(), c};
        Edge b = {u, (int)adj[u].size(), 0};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    int dfs(int u, int t, int pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int &cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
            Edge &e = adj[u][cid];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                int tr = dfs(e.to, t, min(pushed, e.cap));
                if (tr > 0) {
                    e.cap -= tr;
                    adj[e.to][e.rev].cap += tr;
                    return tr;
                }
            }
        }
        return 0;
    }

    // Compute max-flow up to flowLimit
    int maxFlow(int s, int t, int flowLimit) {
        int flow = 0;
        while (flow < flowLimit && bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (flow < flowLimit) {
                int pushed = dfs(s, t, flowLimit - flow);
                if (pushed == 0) break;
                flow += pushed;
            }
        }
        return flow;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_no = 0;
    // Read test cases until EOF
    while (!inf.eof()) {
        case_no++;
        setTestCase(case_no);
        ensuref(case_no <= 100000, "Too many test cases: %d", case_no);

        // Read v, e
        int v = inf.readInt(3, 1000, "v");
        inf.readSpace();
        int e = inf.readInt(3, 10000, "e");
        inf.readEoln();

        // To detect parallel edges
        vector<vector<char>> seen(v+1, vector<char>(v+1, 0));
        vector< tuple<int,int,int> > edges;
        edges.reserve(e);

        for (int i = 0; i < e; i++) {
            int a = inf.readInt(1, v, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, v, "b_i");
            inf.readSpace();
            int c = inf.readInt(1, 100, "c_i");
            inf.readEoln();

            // No self-loops
            ensuref(a != b, "Self-loop detected at edge %d: (%d,%d)", i+1, a, b);
            // No parallel edges
            ensuref(!seen[a][b], "Parallel edge detected at edge %d: (%d->%d)", i+1, a, b);
            seen[a][b] = 1;

            edges.emplace_back(a, b, c);
        }

        // Build flow network to check at least two internally vertex- and edge-disjoint paths
        // Node-splitting: for each u in [1..v], in-node = u-1, out-node = v + (u-1)
        int N = 2 * v;
        Dinic dinic(N);
        int SRC = v + (1 - 1); // out(1)
        int SNK = (v - 1);     // in(v)

        // Add in->out edges with capacity = 1 for internal, = 2 for source and sink
        for (int u = 1; u <= v; u++) {
            int in_u = u - 1;
            int out_u = v + (u - 1);
            int cap = (u == 1 || u == v) ? 2 : 1;
            dinic.addEdge(in_u, out_u, cap);
        }

        // Add edges out(a) -> in(b) with cap=1
        for (auto &t : edges) {
            int a, b, c;
            tie(a, b, c) = t;
            int out_a = v + (a - 1);
            int in_b  = (b - 1);
            dinic.addEdge(out_a, in_b, 1);
        }

        int flow = dinic.maxFlow(SRC, SNK, 2);
        ensuref(flow >= 2, "Less than two disjoint paths from 1 to %d", v);
    }

    inf.readEof();
    return 0;
}

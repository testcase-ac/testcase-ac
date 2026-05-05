#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Simple Kosaraju SCC to check strong connectivity
void dfs1(int v, const vector<vector<int>>& g, vector<int>& used, vector<int>& order) {
    used[v] = 1;
    for (int to : g[v]) if (!used[to]) dfs1(to, g, used, order);
    order.push_back(v);
}

void dfs2(int v, const vector<vector<int>>& gr, vector<int>& comp, int c) {
    comp[v] = c;
    for (int to : gr[v]) if (comp[to] == -1) dfs2(to, gr, comp, c);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 200000;
    const int M_MAX = 500000;

    int N = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(0, M_MAX, "M");
    inf.readEoln();

    vector<vector<int>> g(N + 1), gr(N + 1);

    for (int i = 0; i < M; ++i) {
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int w = inf.readInt(1, N, "w");
        inf.readEoln();

        ensuref(v != w, "Self-loop detected at flight %d: (%d -> %d)", i + 1, v, w);

        g[v].push_back(w);
        gr[w].push_back(v);
    }

    // Global property implied by problem:
    // For the given input, it is NOT guaranteed that from any start all nodes are reachable.
    // The problem does not impose such a restriction, so we do NOT enforce connectivity here.
    // However, we can still safely check internal graph-related invariants if they were stated,
    // which they are not beyond bounds and no self-loops. Multiple edges are allowed.

    // No extra global constraints specified, so we only ensure format & local constraints.

    inf.readEof();
}

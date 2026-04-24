#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 99, "N");
    ensuref(N % 2 == 1, "N must be odd, found N=%d", N);
    inf.readSpace();
    long long maxM = 1LL * N * (N - 1) / 2;
    int M = inf.readInt(1, maxM, "M");
    inf.readEoln();

    // Read comparisons, ensure no loops, no duplicates, build graph
    vector<vector<int>> adj(N + 1);
    set<pair<int,int>> seen;
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v,
                "Comparison %d is a loop: ball %d compared with itself", i, u);
        ensuref(seen.insert({u, v}).second,
                "Duplicate comparison %d: (%d, %d) already exists", i, u, v);
        adj[u].push_back(v);
    }

    // Check for cycles: comparisons must form a DAG since weights are distinct
    vector<int> color(N + 1, 0); // 0=unvisited,1=visiting,2=done
    function<bool(int)> dfs = [&](int u) {
        color[u] = 1;
        for (int v : adj[u]) {
            if (color[v] == 1) return true;
            if (color[v] == 0 && dfs(v)) return true;
        }
        color[u] = 2;
        return false;
    };
    for (int i = 1; i <= N; i++) {
        if (color[i] == 0 && dfs(i)) {
            ensuref(false, "Cycle detected involving ball %d", i);
        }
    }

    inf.readEof();
    return 0;
}

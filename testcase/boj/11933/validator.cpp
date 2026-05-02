#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 500000;
    const int MAX_Q = 100000;

    int N = inf.readInt(2, MAX_N, "N");
    inf.readSpace();
    int Q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    // Read tree edges
    vector<vector<int>> adj(N);
    vector<int> parent(N, -1);
    vector<int> deg(N, 0);
    long long maxEdge = 100000000LL;

    for (int i = 0; i < N - 1; ++i) {
        int A = inf.readInt(0, N - 1, "A_i");
        inf.readSpace();
        int B = inf.readInt(0, N - 1, "B_i");
        inf.readSpace();
        int D = inf.readInt(1, (int)maxEdge, "D_i");
        inf.readEoln();

        ensuref(A != B, "Edge %d has same endpoints (%d, %d)", i, A, B);

        adj[A].push_back(B);
        adj[B].push_back(A);
        deg[A]++;
        deg[B]++;
    }

    // Check connectivity: BFS from node 0
    vector<int> vis(N, 0);
    queue<int> qq;
    qq.push(0);
    vis[0] = 1;
    int seen = 1;

    while (!qq.empty()) {
        int v = qq.front(); qq.pop();
        for (int to : adj[v]) {
            if (!vis[to]) {
                vis[to] = 1;
                seen++;
                qq.push(to);
            }
        }
    }
    ensuref(seen == N, "Graph is not connected: only %d of %d nodes reachable", seen, N);

    long long sumS = 0, sumT = 0;

    for (int j = 0; j < Q; ++j) {
        // Marking arrays per query
        // Use local vector<char> sized N is too big per query; use set of used and check distinctness via unordered_set.
        // But N up to 5e5, per query S_j+T_j up to N-1, total up to 2e6, so per-query unordered_set of size S_j+T_j is fine.
        int Sj = inf.readInt(1, N - 1, "S_j");
        inf.readSpace();
        int Tj = inf.readInt(1, N - 1, "T_j");
        inf.readEoln();

        sumS += Sj;
        sumT += Tj;

        ensuref(sumS <= 1000000LL, "Sum of all S_j exceeds 1e6 (current sum %lld at query %d)", sumS, j);
        ensuref(sumT <= 1000000LL, "Sum of all T_j exceeds 1e6 (current sum %lld at query %d)", sumT, j);

        int total = Sj + Tj;
        // We must ensure all X and Y are pairwise distinct
        unordered_set<int> used;
        used.reserve(total * 2);

        // Read X_j,k
        for (int k = 0; k < Sj; ++k) {
            int x = inf.readInt(0, N - 1, "X_j,k");
            if (k + 1 < Sj) inf.readSpace();
            used.insert(x);
        }
        inf.readEoln();
        ensuref((int)used.size() == Sj, "Query %d: X_j,k values must be distinct", j);

        // Read Y_j,k
        size_t beforeY = used.size();
        for (int k = 0; k < Tj; ++k) {
            int y = inf.readInt(0, N - 1, "Y_j,k");
            if (k + 1 < Tj) inf.readSpace();
            used.insert(y);
        }
        inf.readEoln();
        ensuref((int)used.size() == Sj + Tj, "Query %d: X_j,k and Y_j,k must be pairwise distinct", j);
    }

    inf.readEof();
}

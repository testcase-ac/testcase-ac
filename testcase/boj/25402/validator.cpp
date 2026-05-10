#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 250000;
    const int MAXQ = 100000;
    const long long MAXSUMK = 1000000LL;

    int N = inf.readInt(2, MAXN, "N");
    inf.readEoln();

    vector<vector<int>> adj(N + 1);
    // read edges
    for (int i = 0; i < N - 1; ++i) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();

        ensuref(A != B, "Edge %d has same endpoints: %d %d", i + 1, A, B);
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    // Check that the graph is a tree: connected and N-1 edges
    // We already have exactly N-1 edges; now check connectivity.
    vector<int> q;
    q.reserve(N);
    vector<char> vis(N + 1, 0);
    q.push_back(1);
    vis[1] = 1;
    for (size_t qi = 0; qi < q.size(); ++qi) {
        int v = q[qi];
        for (int to : adj[v]) {
            if (!vis[to]) {
                vis[to] = 1;
                q.push_back(to);
            }
        }
    }
    ensuref((int)q.size() == N, "Graph is not connected, visited %d of %d nodes", (int)q.size(), N);

    int Q = inf.readInt(1, MAXQ, "Q");
    inf.readEoln();

    long long sumK = 0;
    vector<char> used(N + 1);

    for (int qi = 0; qi < Q; ++qi) {
        setTestCase(qi + 1);

        int K = inf.readInt(1, N, "K");
        sumK += K;
        ensuref(sumK <= MAXSUMK, "Sum of K over queries exceeds %lld (at query %d)", MAXSUMK, qi + 1);

        if (K > 0) inf.readSpace();

        // reset used markers for this query using versioning pattern (manual clear of used items)
        vector<int> picked;
        picked.reserve(K);

        for (int i = 0; i < K; ++i) {
            int s = inf.readInt(1, N, "s_i");
            if (i + 1 < K) inf.readSpace();

            ensuref(!used[s], "Duplicate vertex %d in query %d", s, qi + 1);
            used[s] = 1;
            picked.push_back(s);
        }
        inf.readEoln();

        // clear marks
        for (int v : picked) used[v] = 0;
    }

    inf.readEof();
}

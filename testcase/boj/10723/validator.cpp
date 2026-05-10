#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long total_n = 0, total_m = 0;
    for (int tc = 1; tc <= T; ++tc) {
        // 2. Read n, m
        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100000, "m");
        inf.readEoln();

        total_n += n;
        total_m += m;
        ensuref(total_n <= 1000000, "Sum of n over all test cases exceeds 1,000,000 (now %lld)", total_n);
        ensuref(total_m <= 1000000, "Sum of m over all test cases exceeds 1,000,000 (now %lld)", total_m);

        // 3. Read n-1 initial roads
        // The i-th line (1 <= i <= n-1): u_i, c_i (0 <= u_i < i, 0 <= c_i <= 10^7)
        vector<vector<int>> adj(n);
        set<pair<int,int>> initial_edge_set;
        for (int i = 1; i < n; ++i) {
            int u = inf.readInt(0, i-1, "u_i");
            inf.readSpace();
            int c = inf.readInt(0, 10000000, "c_i");
            inf.readEoln();

            // No self-loops possible by constraint (u < i, i >= 1, so u != i)
            int a = min(u, i), b = max(u, i);
            ensuref(!initial_edge_set.count({a, b}), "Duplicate initial edge between %d and %d", a, b);
            initial_edge_set.insert({a, b});

            adj[u].push_back(i);
            adj[i].push_back(u);
        }

        // Check that the initial roads form a connected tree (n nodes, n-1 edges, connected, acyclic)
        // Since the input format is "for i=1..n-1, u_i < i", this is a standard rooted tree construction.
        // But let's check for connectivity anyway.
        vector<bool> visited(n, false);
        vector<int> stack;
        stack.push_back(0);
        visited[0] = true;
        int cnt = 1;
        while (!stack.empty()) {
            int v = stack.back(); stack.pop_back();
            for (int to : adj[v]) {
                if (!visited[to]) {
                    visited[to] = true;
                    stack.push_back(to);
                    ++cnt;
                }
            }
        }
        ensuref(cnt == n, "Initial roads do not connect all cities (connected component size %d, expected %d)", cnt, n);

        // 4. Read m new roads
        for (int j = 0; j < m; ++j) {
            int u = inf.readInt(0, n-1, "u_j");
            inf.readSpace();
            int v = inf.readInt(0, n-1, "v_j");
            inf.readSpace();
            int c = inf.readInt(0, 10000000, "c_j");
            inf.readEoln();

            // Self-loops ARE ALLOWED for new roads (see sample input: 0 0 2 is allowed)
            // No further checks needed for new roads (multi-edges allowed, self-loops allowed)
        }
    }

    inf.readEof();
}

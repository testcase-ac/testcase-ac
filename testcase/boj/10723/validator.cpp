#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    long long totalM = 0;
    for (int tc = 1; tc <= T; ++tc) {
        int n = inf.readInt(1, 2000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 2000, "m");
        inf.readEoln();

        totalN += n;
        totalM += m;
        // CHECK: The statement gives no T or aggregate bound; cap total size to keep validation practical.
        ensuref(totalN <= 1000000, "sum of n exceeds 1000000 after testcase %d", tc);
        ensuref(totalM <= 1000000, "sum of m exceeds 1000000 after testcase %d", tc);

        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            int u = inf.readInt(0, i - 1, "u_i");
            inf.readSpace();
            int c = inf.readInt(0, 10000000, "c_i");
            inf.readEoln();

            adj[u].push_back(i);
            adj[i].push_back(u);
        }

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
        ensuref(cnt == n, "initial roads do not connect all cities in testcase %d", tc);

        for (int j = 0; j < m; ++j) {
            int u = inf.readInt(0, n-1, "u_j");
            inf.readSpace();
            int v = inf.readInt(0, n-1, "v_j");
            inf.readSpace();
            int c = inf.readInt(0, 10000000, "c_j");
            inf.readEoln();
        }
    }

    inf.readEof();
}

#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();
    for (int tc = 0; tc < T; tc++) {
        setTestCase(tc + 1);

        // Read N and M
        int N = inf.readInt(1, 300, "N");
        inf.readSpace();
        int M = inf.readInt(1, 3000, "M");
        inf.readEoln();

        // Build graph and check for loops
        vector<vector<int>> g(N + 1);
        vector<int> indeg(N + 1, 0);
        for (int i = 0; i < M; i++) {
            int A = inf.readInt(1, N, "A");
            inf.readSpace();
            int B = inf.readInt(1, N, "B");
            inf.readEoln();
            ensuref(A != B,
                    "Loop detected at edge %d of test case %d: %d -> %d",
                    i + 1, tc + 1, A, B);
            g[A].push_back(B);
            indeg[B]++;
        }

        // Check the graph is acyclic via Kahn's algorithm
        queue<int> q;
        for (int i = 1; i <= N; i++) {
            if (indeg[i] == 0) q.push(i);
        }
        int visited = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            visited++;
            for (int v : g[u]) {
                if (--indeg[v] == 0)
                    q.push(v);
            }
        }
        ensuref(visited == N,
                "Graph contains a cycle in test case %d", tc + 1);
    }

    inf.readEof();
    return 0;
}

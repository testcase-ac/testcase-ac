#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 500, "N");
    inf.readSpace();
    int maxM = N * (N - 1) / 2;
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();

    // Build graph of comparisons a -> b meaning a is shorter than b
    vector<vector<int>> adj(N + 1);
    vector<vector<bool>> seen(N + 1, vector<bool>(N + 1, false));
    vector<int> indeg(N + 1, 0);

    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();
        ensuref(a != b,
                "Self-comparison detected at comparison index %d: (%d, %d)",
                i, a, b);
        ensuref(!seen[a][b],
                "Duplicate comparison detected at comparison index %d: (%d, %d)",
                i, a, b);
        seen[a][b] = true;
        adj[a].push_back(b);
        indeg[b]++;
    }

    // Ensure no cycles (i.e., no contradictory comparisons)
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }
    int visited = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited++;
        for (int v : adj[u]) {
            if (--indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    ensuref(visited == N,
            "Cycle detected: input comparisons imply a contradiction");

    inf.readEof();
    return 0;
}

#include "testlib.h"
#include <queue>
#include <vector>
using namespace std;

struct Edge {
    int to;
    int w;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, M, t
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 30000, "M");
    inf.readSpace();
    int t = inf.readInt(1, 10, "t");
    inf.readEoln();

    // Read edges
    vector<vector<Edge>> g(N + 1);
    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readSpace();
        int C = inf.readInt(1, 10000, "C");
        inf.readEoln();

        ensuref(A != B, "Self-loop detected at edge %d: (%d, %d)", i + 1, A, B);

        g[A].push_back({B, C});
        g[B].push_back({A, C});
    }

    // Graph must be connected (statement: "모든 도시의 쌍에는 ... 경로가 있다")
    if (N == 1) {
        ensuref(M == 0, "With N = 1, M must be 0, but got %d", M);
    } else {
        ensuref(M >= N - 1,
                "A connected graph with N=%d must have at least N-1 edges, but M=%d",
                N, M);
    }

    // BFS/DFS to check actual connectivity from node 1
    vector<char> vis(N + 1, 0);
    queue<int> q;
    vis[1] = 1;
    q.push(1);
    int visitedCnt = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        ++visitedCnt;
        for (auto &e : g[v]) {
            if (!vis[e.to]) {
                vis[e.to] = 1;
                q.push(e.to);
            }
        }
    }
    ensuref(visitedCnt == N,
            "Graph is not connected: reachable %d out of %d nodes", visitedCnt, N);

    inf.readEof();
}

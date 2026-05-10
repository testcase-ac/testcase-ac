#include "testlib.h"
#include <set>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, X
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int maxM = N * (N - 1) / 2;
    int M = inf.readInt(1, min(maxM, 500000), "M");
    inf.readSpace();
    int X = inf.readInt(1, N, "X");
    inf.readEoln();

    // 2. Read M lines of (A, B)
    // - 1 <= A, B <= N
    // - A != B
    // - No duplicate (A,B)
    // - Each (A,B): A is better than B
    // - No cycles (implied: "입력된 값이 정확함이 보장된다" - but we must check for cycles)
    set<pair<int, int>> seen;
    vector<vector<int>> adj(N + 1); // 1-based
    vector<int> indeg(N + 1, 0);

    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readEoln();

        ensuref(A != B, "A == B at line %d: (%d, %d)", i + 2, A, B);
        ensuref(!seen.count({A, B}), "Duplicate pair at line %d: (%d, %d)", i + 2, A, B);
        seen.insert({A, B});
        adj[A].push_back(B);
        indeg[B]++;
    }

    // 3. Check for cycles (the input must be a DAG)
    // We'll use Kahn's algorithm for topological sort.
    vector<int> indeg_copy = indeg;
    queue<int> q;
    int cnt = 0;
    for (int i = 1; i <= N; ++i) {
        if (indeg_copy[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cnt++;
        for (int v : adj[u]) {
            indeg_copy[v]--;
            if (indeg_copy[v] == 0) q.push(v);
        }
    }
    ensuref(cnt == N, "Input graph contains a cycle (not a DAG): only %d/%d nodes can be topologically sorted", cnt, N);

    inf.readEof();
}

#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 2;
    const int N_MAX = 200000;
    const int M_MIN = 1;
    const int M_MAX = 200000;
    const int V_MIN = 2;
    const int C_MIN = 1;
    const int C_MAX = 1000000;
    const long long K_MIN = 1LL;
    const long long K_MAX = 1000000000LL;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readSpace();
    int V = inf.readInt(V_MIN, N, "V");
    inf.readEoln();

    // Read C_i values
    vector<int> C(N + 1);
    for (int i = 1; i <= N; ++i) {
        C[i] = inf.readInt(C_MIN, C_MAX, "C_i");
        if (i < N) inf.readSpace();
    }
    inf.readEoln();

    // Simulate the structure and verify it is a valid "snail list":
    // 1 -> 2 -> ... -> N-1 -> N -> V, where 2 <= V <= N, hence a cycle excluding node 1.
    // Also check the global property: the answer is well-defined for arbitrarily long walks,
    // which is guaranteed by the unique outgoing edge and the presence of a cycle.

    // Build next pointer array (1-based)
    vector<int> nxt(N + 1);
    for (int i = 1; i <= N - 1; ++i) {
        nxt[i] = i + 1;
    }
    nxt[N] = V;

    // Verify functional graph (outdegree == 1 already guaranteed by construction).
    // Check that from node 1, following edges visits exactly N distinct nodes
    // and eventually forms a cycle that does NOT include node 1.
    vector<int> state(N + 1, 0); // 0 = unvisited, 1 = visiting, 2 = exited
    int cur = 1;
    int steps = 0;
    while (state[cur] == 0) {
        state[cur] = 1;
        cur = nxt[cur];
        ++steps;
        ensuref(steps <= N + 5, "Traversal from node 1 exceeded expected steps; possible structure error");
    }
    // We encountered a previously visited node 'cur'
    ensuref(state[cur] == 1, "Detected an invalid structure: should form exactly one cycle reachable from 1");
    // cur is in the cycle
    // Ensure node 1 is not part of the cycle (matches definition: N points to a node except 1)
    ensuref(cur != 1, "Cycle must not include node 1");

    // Check that we have visited all N distinct nodes from 1
    int visitedCount = 0;
    for (int i = 1; i <= N; ++i) {
        if (state[i] != 0) ++visitedCount;
    }
    ensuref(visitedCount == N,
            "From node 1 the list must visit all N nodes exactly once before entering the cycle; visited=%d, N=%d",
            visitedCount, N);

    // Read queries K
    for (int i = 0; i < M; ++i) {
        long long K = inf.readLong(K_MIN, K_MAX, "K");
        inf.readEoln();
        // No extra constraints depending on K, so nothing else to check
    }

    inf.readEof();
}

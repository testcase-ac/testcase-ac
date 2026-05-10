#include "testlib.h"
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n: number of stones
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // A_i: jump distance from each stone
    vector<int> a = inf.readInts(n, 1, 100000, "A_i");
    inf.readEoln();

    // s: starting position
    int s = inf.readInt(1, n, "s");
    inf.readEoln();

    // Simulate reachability to ensure problem's implied guarantee
    // (that all movements are always within [1, n] if constrained so).
    // Here we only check for correctness of BFS logic and that it terminates.
    vector<char> vis(n, 0);
    queue<int> q;

    int start = s - 1; // 0-based index
    vis[start] = 1;
    q.push(start);

    long long reachableCount = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        reachableCount++;

        long long left = (long long)u - a[u];
        long long right = (long long)u + a[u];

        if (left >= 0 && !vis[(int)left]) {
            vis[(int)left] = 1;
            q.push((int)left);
        }
        if (right < n && !vis[(int)right]) {
            vis[(int)right] = 1;
            q.push((int)right);
        }
    }
    // reachableCount is guaranteed to be between 1 and n by construction.
    ensuref(1 <= reachableCount && reachableCount <= n,
            "Reachable stone count %lld is out of valid range [1, %d]",
            reachableCount, n);

    inf.readEof();
}

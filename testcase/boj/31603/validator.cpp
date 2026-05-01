#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXQ = 100000;

    int n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    int q = inf.readInt(1, MAXQ, "q");
    inf.readEoln();

    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[i] = inf.readInt(0, n, "p_i");
        if (i < n) inf.readSpace();
    }
    inf.readEoln();

    // Check that p defines a rooted tree
    int rootCount = 0;
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        if (p[i] == 0) {
            rootCount++;
            root = i;
        } else {
            // parent must be a valid node index
            ensuref(1 <= p[i] && p[i] <= n,
                    "Parent index p[%d]=%d is out of range [1,%d] or 0 for root",
                    i, p[i], n);
        }
    }
    ensuref(rootCount == 1, "There must be exactly one root, found %d", rootCount);

    // Build adjacency list (children)
    vector<vector<int>> children(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (p[i] != 0) {
            children[p[i]].push_back(i);
            indeg[i]++;
        }
    }

    // Check there are no cycles and all nodes reachable from root
    queue<int> qu;
    vector<int> visited(n + 1, 0);
    qu.push(root);
    visited[root] = 1;
    int visitedCount = 0;
    while (!qu.empty()) {
        int v = qu.front();
        qu.pop();
        visitedCount++;
        for (int to : children[v]) {
            if (!visited[to]) {
                visited[to] = 1;
                qu.push(to);
            }
        }
    }
    ensuref(visitedCount == n,
            "The parent array must represent a single connected rooted tree; reachable %d of %d nodes",
            visitedCount, n);

    // Additionally ensure no node has more than one parent (already implied by input format),
    // and that no self-parenting occurs (p[i] != i)
    for (int i = 1; i <= n; ++i) {
        ensuref(p[i] != i, "Node %d cannot be its own parent", i);
    }

    // Now read queries and validate bounds: 1 <= k_j <= n^2
    // n^2 fits into 64-bit: n <= 1e5 -> n^2 <= 1e10
    long long maxK = 1LL * n * n;
    for (int j = 1; j <= q; ++j) {
        long long kj = inf.readLong(1LL, maxK, "k_j");
        inf.readEoln();
        (void)kj; // no further structural constraints
    }

    inf.readEof();
}

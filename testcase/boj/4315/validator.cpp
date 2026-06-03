#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalN = 0;
    int caseIndex = 1;
    while (true) {
        int n = inf.readInt(0, 10000, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        setTestCase(caseIndex++);
        totalN += n;
        // CHECK: The statement does not bound the number of cases; cap total
        // vertices to keep validation work within the local scalar-token policy.
        ensuref(totalN <= 1000000, "too many total vertices: %lld", totalN);

        vector<int> seen(n + 1, 0);
        vector<int> indegree(n + 1, 0);
        vector<vector<int>> children(n + 1);
        long long marbleSum = 0;
        int edgeCount = 0;

        for (int i = 1; i <= n; ++i) {
            int v = inf.readInt(1, n, "v");
            inf.readSpace();
            int marbles = inf.readInt(0, n, "marbles");
            inf.readSpace();
            int d = inf.readInt(0, n - 1, "d");
            marbleSum += marbles;

            ensuref(!seen[v], "vertex %d appears more than once", v);
            seen[v] = 1;

            edgeCount += d;
            ensuref(edgeCount <= n - 1, "too many child edges: %d", edgeCount);

            for (int j = 1; j <= d; ++j) {
                inf.readSpace();
                int child = inf.readInt(1, n, "child");
                ensuref(child != v, "vertex %d lists itself as a child", v);
                ++indegree[child];
                ensuref(indegree[child] <= 1, "vertex %d has multiple parents", child);
                children[v].push_back(child);
            }
            inf.readEoln();
        }

        ensuref(marbleSum == n, "total marbles must be n: got %lld, expected %d", marbleSum, n);
        ensuref(edgeCount == n - 1, "rooted tree must have n - 1 edges: got %d", edgeCount);

        int root = -1;
        for (int v = 1; v <= n; ++v) {
            ensuref(seen[v], "missing vertex row for %d", v);
            if (indegree[v] == 0) {
                ensuref(root == -1, "multiple roots: %d and %d", root, v);
                root = v;
            }
        }
        ensuref(root != -1, "rooted tree must have a root");

        vector<int> visited(n + 1, 0);
        queue<int> q;
        q.push(root);
        visited[root] = 1;
        int visitedCount = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            ++visitedCount;
            for (int child : children[v]) {
                ensuref(!visited[child], "cycle or duplicate reachability at vertex %d", child);
                visited[child] = 1;
                q.push(child);
            }
        }
        ensuref(visitedCount == n, "rooted tree must be connected from root %d", root);
    }

    inf.readEof();
}

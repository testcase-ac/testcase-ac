#include "testlib.h"

#include <queue>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<pair<int, int>> children(n + 1);
    vector<int> parent(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int left = inf.readInt(-1, n, "U");
        ensuref(left == -1 || left >= 2, "left child of node %d must be -1 or in [2, N], got %d", i, left);
        inf.readSpace();
        int right = inf.readInt(-1, n, "V");
        ensuref(right == -1 || right >= 2, "right child of node %d must be -1 or in [2, N], got %d", i, right);
        inf.readEoln();

        ensuref(left == -1 || right == -1 || left != right,
                "node %d has the same node %d as both children", i, left);

        children[i] = {left, right};
        for (int child : {left, right}) {
            if (child == -1) {
                continue;
            }
            ensuref(parent[child] == 0,
                    "node %d has multiple parents: %d and %d", child, parent[child], i);
            parent[child] = i;
        }
    }

    for (int node = 2; node <= n; ++node) {
        ensuref(parent[node] != 0, "node %d is not reachable from root 1", node);
    }

    vector<char> visited(n + 1, false);
    queue<int> q;
    visited[1] = true;
    q.push(1);
    int reachable = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ++reachable;

        for (int child : {children[node].first, children[node].second}) {
            if (child == -1) {
                continue;
            }
            ensuref(!visited[child], "cycle or duplicate reachability involving node %d", child);
            visited[child] = true;
            q.push(child);
        }
    }
    ensuref(reachable == n, "only %d of %d nodes are reachable from root 1", reachable, n);

    inf.readLong(1LL, 1000000000000000000LL, "K");
    inf.readEoln();
    inf.readEof();
}

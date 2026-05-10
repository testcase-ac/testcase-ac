#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // 2. Read parent array, and validate constraints
    vector<int> parent(N+1, -2); // 1-based, parent[1..N]
    int root_count = 0, root_idx = -1;
    for (int i = 1; i <= N; ++i) {
        int p = inf.readInt(-1, N, "parent_i");
        if (i < N) inf.readEoln();
        else inf.readEoln(); // last line

        if (p == -1) {
            root_count++;
            root_idx = i;
        } else {
            ensuref(p >= 1 && p <= N, "parent[%d] = %d is not in [1, N] or -1", i, p);
            ensuref(p != i, "Employee %d cannot be their own boss", i);
        }
        parent[i] = p;
    }

    // 3. There must be exactly one root (the president)
    ensuref(root_count == 1, "There must be exactly one president (parent == -1), found %d", root_count);

    // 4. Build the tree and check for cycles and connectivity
    vector<vector<int>> children(N+1);
    for (int i = 1; i <= N; ++i) {
        int p = parent[i];
        if (p != -1) {
            children[p].push_back(i);
        }
    }

    // 5. Check for cycles and connectivity using BFS/DFS from root
    vector<bool> visited(N+1, false);
    queue<int> q;
    q.push(root_idx);
    visited[root_idx] = true;
    int visit_cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            ensuref(!visited[v], "Cycle detected or multiple parents for node %d", v);
            visited[v] = true;
            ++visit_cnt;
            q.push(v);
        }
    }
    ensuref(visit_cnt == N, "The hierarchy is not connected: only %d/%d nodes reachable from president", visit_cnt, N);

    inf.readEof();
}

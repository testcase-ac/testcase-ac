#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // 2. Read tree structure
    vector<vector<int>> children(N + 1); // 1-based
    vector<int> parent(N + 1, 0); // parent[i] = parent of i, 0 if root
    vector<int> child_count(N + 1, 0);
    set<int> all_children;
    for (int i = 1; i <= N; ++i) {
        int cnt = inf.readInt(0, N - 1, "child_count");
        child_count[i] = cnt;
        vector<int> ch;
        set<int> local_set;
        for (int j = 0; j < cnt; ++j) {
            inf.readSpace();
            int c = inf.readInt(1, N, "child");
            ensuref(c != i, "Folder %d cannot be its own child", i);
            ensuref(local_set.count(c) == 0, "Duplicate child %d in folder %d", c, i);
            local_set.insert(c);
            ch.push_back(c);
            all_children.insert(c);
        }
        children[i] = ch;
        inf.readEoln();
    }

    // 2.1. Check for unique parent for each node except root
    for (int i = 1; i <= N; ++i) {
        for (int c : children[i]) {
            ensuref(parent[c] == 0, "Folder %d has multiple parents (at least %d and %d)", c, parent[c], i);
            parent[c] = i;
        }
    }
    // 2.2. Root must be 1, and must not be child of anyone
    ensuref(parent[1] == 0, "Folder 1 must be the root and have no parent");
    // 2.3. All other nodes must have exactly one parent
    for (int i = 2; i <= N; ++i) {
        ensuref(parent[i] != 0, "Folder %d does not have a parent (not connected to root)", i);
    }
    // 2.4. No node is child of itself (already checked above)
    // 2.5. No duplicate children in a folder (already checked above)
    // 2.6. No two folders share a child (already checked above)

    // 2.7. The structure must be a tree (i.e., connected and acyclic)
    // Let's check for cycles and connectivity using BFS from root
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int visit_cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            ensuref(!visited[v], "Cycle detected at folder %d", v);
            visited[v] = true;
            ++visit_cnt;
            q.push(v);
        }
    }
    ensuref(visit_cnt == N, "Tree is not connected: only %d/%d nodes reachable from root", visit_cnt, N);

    // 3. Read Q commands
    bool has_move = false;
    for (int i = 0; i < Q; ++i) {
        string cmd = inf.readToken("[^ \n]+", "command");
        if (cmd == "toggle") {
            inf.readEoln();
        } else if (cmd == "move") {
            has_move = true;
            inf.readSpace();
            int k = inf.readInt(-N, N, "k");
            inf.readEoln();
        } else {
            ensuref(false, "Unknown command '%s' at line %d", cmd.c_str(), N + 1 + i + 1);
        }
    }
    ensuref(has_move, "At least one move command must be present");

    inf.readEof();
}

#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, L
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(0, N-1, "M");
    inf.readSpace();
    int L = inf.readInt(1, 10000, "L");
    inf.readEoln();

    // 2. Prepare for edge validation
    set<pair<int,int>> edges;
    vector<int> deg(N, 0);

    // 3. Read M edges
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(0, N-1, "A[i]");
        inf.readSpace();
        int b = inf.readInt(0, N-1, "B[i]");
        inf.readSpace();
        int t = inf.readInt(1, 10000, "T[i]");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i+1, a, b);

        // Check for multiple edges (undirected)
        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}), "Multiple edge detected between %d and %d (edge %d)", u, v, i+1);
        edges.insert({u, v});

        // For subtask 1/3/4, degree constraints
        deg[a]++;
        deg[b]++;
    }

    // 4. Subtask-specific checks
    // Subtask 1,2,3: M == N-2
    // Subtask 1: Each node degree 1 or 2, and the graph is two simple paths (two components, each a path)
    // Subtask 4: Each node degree at most 1

    // For all subtasks, check that there are no duplicate edges or self-loops (already done above)

    // For subtask 1, 2, 3: M == N-2
    if (M == N-2) {
        // Subtask 1: Each node degree 1 or 2, and two components, each a path
        // Subtask 2: N <= 100 (no extra check)
        // Subtask 3: No extra check

        // For subtask 1: Each node degree 1 or 2, and two components, each a path
        // We can't know which subtask we are in, but we can check the property for all M==N-2 cases
        bool all_deg_1_or_2 = true;
        for (int i = 0; i < N; ++i) {
            if (deg[i] < 1 || deg[i] > 2) {
                all_deg_1_or_2 = false;
                break;
            }
        }
        // If all degrees are 1 or 2, check that the graph consists of exactly two simple paths
        if (all_deg_1_or_2) {
            // Find connected components
            vector<bool> vis(N, false);
            int comp_cnt = 0;
            for (int i = 0; i < N; ++i) {
                if (!vis[i]) {
                    // BFS/DFS from i
                    int cnt = 0;
                    int deg1 = 0;
                    int cur = i;
                    int prev = -1;
                    while (true) {
                        vis[cur] = true;
                        cnt++;
                        if (deg[cur] == 1) deg1++;
                        // Find next neighbor
                        int next = -1;
                        for (int j = 0; j < N; ++j) {
                            if (j == prev) continue;
                            int u = min(cur, j), v = max(cur, j);
                            if (edges.count({u, v})) {
                                if (!vis[j]) {
                                    next = j;
                                    break;
                                }
                            }
                        }
                        if (next == -1) break;
                        prev = cur;
                        cur = next;
                    }
                    // For a path, must have exactly 2 nodes of degree 1, rest degree 2
                    ensuref(deg1 == 2, "Component %d is not a simple path (deg1=%d)", comp_cnt+1, deg1);
                    comp_cnt++;
                }
            }
            ensuref(comp_cnt == 2, "Number of components is not 2 for subtask 1 (got %d)", comp_cnt);
        }
    }

    // Subtask 4: Each node degree at most 1
    bool all_deg_leq_1 = true;
    for (int i = 0; i < N; ++i) {
        if (deg[i] > 1) {
            all_deg_leq_1 = false;
            break;
        }
    }
    if (all_deg_leq_1) {
        // For subtask 4, nothing else to check
    }

    // 5. Global property: The graph is a forest (acyclic, undirected), possibly disconnected
    // The problem says: "임의의 빌라봉 쌍은 길을 따라서 (직접 또는 간접적으로) 최대 하나의 경로로 연결이 되어 있다."
    // This means the graph is a forest (no cycles, undirected, no multi-edges, no loops)
    // We already checked for multi-edges and loops above.
    // Now check for cycles (i.e., the graph is acyclic)
    // Use Union-Find (DSU) to check for cycles

    vector<int> par(N);
    for (int i = 0; i < N; ++i) par[i] = i;
    function<int(int)> find = [&](int x) {
        if (par[x] != x) par[x] = find(par[x]);
        return par[x];
    };
    for (auto e : edges) {
        int u = e.first, v = e.second;
        int pu = find(u), pv = find(v);
        ensuref(pu != pv, "Cycle detected between %d and %d", u, v);
        par[pu] = pv;
    }

    // 6. No extra tokens/lines
    inf.readEof();
}

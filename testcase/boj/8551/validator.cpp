#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(2, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    // Prepare to store edges and check for duplicates
    set<pair<int,int>> edges;
    vector<vector<int>> adj(n+1); // 1-based

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i+1, a, b);
        ensuref(!edges.count({a, b}), "Multiple edge detected at edge %d: (%d, %d)", i+1, a, b);
        edges.insert({a, b});
        adj[a].push_back(b);
    }

    // Check if there is at least one path from 1 to n
    // (since otherwise the answer is 0, which is not interesting for the problem)
    // But the statement does not guarantee that there is a path, so we do not enforce it.

    // Check global formatting: exactly one EOLN after last line, then EOF
    inf.readEof();

    // No further global properties to check (e.g., no requirement that the answer is at most X, or that the answer always exists).
    // The only constraints are: no self-loops, no multiple edges, 1 <= a,b <= n, a != b, m in [0,100000], n in [2,10000].
}

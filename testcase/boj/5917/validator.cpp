#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 1000000, "l");
        inf.readEoln();

        // CHECK: The statement describes pathways joining fields, so self-loops
        // are treated as invalid even though A_j and B_j are not explicitly
        // stated to be distinct.
        ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);

        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate pathway at edge %d: %d %d", i, a, b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> seen(n + 1, 0);
    queue<int> q;
    seen[1] = 1;
    q.push(1);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int next : graph[cur]) {
            if (!seen[next]) {
                seen[next] = 1;
                q.push(next);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        ensuref(seen[i], "field %d is not connected to field 1", i);
    }

    inf.readEof();
}

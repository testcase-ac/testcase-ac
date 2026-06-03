#include "testlib.h"
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge %d: (%d, %d)", i + 1, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: (%d, %d)", i + 1, a, b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<char> seen(n + 1, false);
    queue<int> q;
    seen[1] = true;
    q.push(1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int next : graph[v]) {
            if (!seen[next]) {
                seen[next] = true;
                q.push(next);
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        ensuref(seen[v], "graph is not connected; vertex %d is unreachable from 1", v);
    }

    inf.readEof();
    return 0;
}

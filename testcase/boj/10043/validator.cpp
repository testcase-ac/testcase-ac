#include "testlib.h"

#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readSpace();
    int k = inf.readInt(n - 1, 10000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000, "C_i");
        inf.readSpace();
        inf.readInt(1, n, "R_i");
        inf.readEoln();
    }

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;
    for (int j = 1; j <= k; ++j) {
        int a = inf.readInt(1, n, "A_j");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "B_j");
        inf.readEoln();

        ensuref(edges.insert({a, b}).second,
                "duplicate road at index %d: (%d, %d)", j, a, b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> seen(n + 1, 0);
    queue<int> q;
    seen[1] = 1;
    q.push(1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (!seen[to]) {
                seen[to] = 1;
                q.push(to);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        ensuref(seen[i], "town %d is not reachable from town 1", i);
    }

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(0, maxEdges, "m");
    inf.readEoln();

    vector<vector<bool>> hasEdge(n + 1, vector<bool>(n + 1, false));
    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "loop at edge index %d: (%d, %d)", i + 1, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i + 1, u, v);
        hasEdge[edge.first][edge.second] = true;
    }

    vector<vector<int>> greaterThan(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int smallerValuePosition = hasEdge[i][j] ? j : i;
            int largerValuePosition = hasEdge[i][j] ? i : j;
            greaterThan[smallerValuePosition].push_back(largerValuePosition);
            ++indegree[largerValuePosition];
        }
    }

    vector<int> ready;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            ready.push_back(i);
        }
    }

    int visited = 0;
    while (!ready.empty()) {
        int u = ready.back();
        ready.pop_back();
        ++visited;
        for (int v : greaterThan[u]) {
            --indegree[v];
            if (indegree[v] == 0) {
                ready.push_back(v);
            }
        }
    }
    ensuref(visited == n, "edge set does not come from any permutation");

    inf.readEof();
}

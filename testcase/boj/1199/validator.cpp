#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            graph[i][j] = inf.readInt(0, 10, "a_ij");
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        ensuref(graph[i][i] == 0, "loop count at vertex %d is %d", i + 1, graph[i][i]);
        for (int j = i + 1; j < n; ++j) {
            ensuref(graph[i][j] == graph[j][i],
                    "matrix is not symmetric at (%d, %d): %d != %d",
                    i + 1,
                    j + 1,
                    graph[i][j],
                    graph[j][i]);
        }
    }

    vector<int> visited(n);
    queue<int> q;
    visited[0] = 1;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0 && !visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        ensuref(visited[i], "vertex %d is not connected to vertex 1", i + 1);
    }

    inf.readEof();
}

#include "testlib.h"

#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(2, 100, "h");
    inf.readSpace();
    int w = inf.readInt(2, 100, "w");
    inf.readEoln();

    vector<vector<pair<int, int>>> graph((h + 1) * (w + 1));
    int edgeCount = 0;

    auto id = [w](int r, int c) {
        return r * (w + 1) + c;
    };

    for (int r = 0; r < h; ++r) {
        string row = inf.readLine("[./\\\\]{2,100}", "row");
        ensuref((int)row.size() == w, "row %d has length %d, expected %d", r + 1,
                (int)row.size(), w);

        for (int c = 0; c < w; ++c) {
            int a = -1;
            int b = -1;
            if (row[c] == '/') {
                a = id(r + 1, c);
                b = id(r, c + 1);
            } else if (row[c] == '\\') {
                a = id(r, c);
                b = id(r + 1, c + 1);
            }

            if (a != -1) {
                graph[a].push_back({b, edgeCount});
                graph[b].push_back({a, edgeCount});
                ++edgeCount;
            }
        }
    }

    ensuref(edgeCount > 0, "polygon must contain at least one edge");

    int start = -1;
    for (int v = 0; v < (int)graph.size(); ++v) {
        int degree = (int)graph[v].size();
        ensuref(degree == 0 || degree == 2, "vertex %d has degree %d", v, degree);
        if (degree == 2 && start == -1) {
            start = v;
        }
    }

    vector<int> seenVertex(graph.size(), 0);
    vector<int> seenEdge(edgeCount, 0);
    queue<int> q;
    q.push(start);
    seenVertex[start] = 1;

    int visitedVertices = 0;
    int visitedEdges = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++visitedVertices;

        for (auto [to, edgeId] : graph[v]) {
            if (!seenEdge[edgeId]) {
                seenEdge[edgeId] = 1;
                ++visitedEdges;
            }
            if (!seenVertex[to]) {
                seenVertex[to] = 1;
                q.push(to);
            }
        }
    }

    for (int v = 0; v < (int)graph.size(); ++v) {
        ensuref(graph[v].empty() || seenVertex[v], "polygon has multiple components");
    }
    ensuref(visitedEdges == edgeCount, "polygon has multiple components");
    ensuref(visitedVertices == edgeCount, "polygon is not one simple cycle");

    inf.readEof();
}

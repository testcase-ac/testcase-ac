#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> treeEdges;

pair<int, int> normalizedEdge(int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    return {u, v};
}

struct Answer {
    int addedCount;
};

Answer readAnswer(InStream& stream, TResult invalidVerdict) {
    int m = stream.readInt(0, n / 5, "M");

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> usedEdges;
    for (auto [u, v] : treeEdges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
        usedEdges.insert(normalizedEdge(u, v));
    }

    for (int i = 0; i < m; ++i) {
        int u = stream.readInt(1, n, format("u[%d]", i + 1).c_str());
        int v = stream.readInt(1, n, format("v[%d]", i + 1).c_str());
        if (u == v) {
            stream.quitf(invalidVerdict, "added edge %d is a self-loop at vertex %d", i + 1, u);
        }

        pair<int, int> edge = normalizedEdge(u, v);
        if (usedEdges.count(edge)) {
            stream.quitf(invalidVerdict,
                         "added edge %d duplicates existing edge (%d, %d)",
                         i + 1,
                         edge.first,
                         edge.second);
        }
        usedEdges.insert(edge);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %d added edge(s)", m);
    }

    int diameter = 0;
    vector<int> dist(n + 1);
    for (int start = 1; start <= n; ++start) {
        fill(dist.begin(), dist.end(), -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : graph[v]) {
                if (dist[to] != -1) {
                    continue;
                }
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }

        for (int v = 1; v <= n; ++v) {
            if (dist[v] == -1) {
                stream.quitf(invalidVerdict,
                             "augmented graph is disconnected: vertex %d cannot reach vertex %d",
                             start,
                             v);
            }
            diameter = max(diameter, dist[v]);
        }
    }

    if (diameter > 10) {
        stream.quitf(invalidVerdict, "augmented graph diameter is %d, expected at most 10", diameter);
    }

    return {m};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "N");
    treeEdges.reserve(max(0, n - 1));
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt(1, n, format("tree_u[%d]", i + 1).c_str());
        int v = inf.readInt(1, n, format("tree_v[%d]", i + 1).c_str());
        treeEdges.push_back({u, v});
    }

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    quitf(_ok,
          "valid augmentation: jury added %d edge(s), participant added %d edge(s)",
          jury.addedCount,
          participant.addedCount);
}

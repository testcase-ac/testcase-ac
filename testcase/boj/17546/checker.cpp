#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

int n, m;
vector<Edge> edges;

struct Claim {
    int removedCount;
};

Claim readClaim(InStream& stream) {
    int r = stream.readInt(0, m / 2, "number of removed corridors");
    vector<char> removed(m + 1, false);

    for (int i = 0; i < r; ++i) {
        int index = stream.readInt(1, m, format("removed corridor[%d]", i + 1).c_str());
        if (removed[index]) {
            stream.quitf(_wa, "corridor index %d is listed more than once", index);
        }
        removed[index] = true;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after removed corridor list");
    }

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 1; i <= m; ++i) {
        if (removed[i]) {
            continue;
        }
        graph[edges[i].from].push_back(edges[i].to);
        ++indegree[edges[i].to];
    }

    queue<int> q;
    for (int vertex = 1; vertex <= n; ++vertex) {
        if (indegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        ++visited;

        for (int next : graph[vertex]) {
            --indegree[next];
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    if (visited != n) {
        stream.quitf(_wa, "remaining graph contains a directed cycle");
    }

    return {r};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.assign(m + 1, {});
    for (int i = 1; i <= m; ++i) {
        edges[i].from = inf.readInt();
        edges[i].to = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok,
          "valid removal set with %d corridors; jury removed %d",
          participant.removedCount,
          jury.removedCount);
}

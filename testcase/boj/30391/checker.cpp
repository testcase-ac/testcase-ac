#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int n, k;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

struct Claim {
    int diameter;
};

int treeDiameter(const vector<vector<int>>& graph) {
    auto farthestFrom = [&](int start) {
        vector<int> dist(n + 1, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);

        int best = start;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] > dist[best]) {
                best = u;
            }
            for (int v : graph[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return pair<int, int>(best, dist[best]);
    };

    int endpoint = farthestFrom(1).first;
    return farthestFrom(endpoint).second;
}

Claim readClaim(InStream& stream, TResult invalidResult, const string& owner) {
    vector<vector<int>> graph(n + 1);
    vector<int> degree(n + 1, 0);
    Dsu dsu(n);

    for (int i = 0; i < n - 1; ++i) {
        int u = stream.readInt(1, n, format("%s edge[%d].u", owner.c_str(), i + 1).c_str());
        int v = stream.readInt(1, n, format("%s edge[%d].v", owner.c_str(), i + 1).c_str());
        if (u == v) {
            stream.quitf(invalidResult, "%s edge[%d] is a self-loop at vertex %d", owner.c_str(), i + 1, u);
        }
        if (!dsu.unite(u, v)) {
            stream.quitf(invalidResult, "%s edge[%d] creates a cycle between %d and %d", owner.c_str(), i + 1, u, v);
        }

        ++degree[u];
        ++degree[v];
        if (degree[u] > k) {
            stream.quitf(invalidResult, "%s vertex %d has degree %d > %d", owner.c_str(), u, degree[u], k);
        }
        if (degree[v] > k) {
            stream.quitf(invalidResult, "%s vertex %d has degree %d > %d", owner.c_str(), v, degree[v], k);
        }

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "%s output has extra tokens after %d edges", owner.c_str(), n - 1);
    }

    int root = dsu.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        if (dsu.find(vertex) != root) {
            stream.quitf(invalidResult, "%s output is disconnected", owner.c_str());
        }
    }

    return {treeDiameter(graph)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 300000, "N");
    k = inf.readInt(2, n - 1, "K");

    Claim jury = readClaim(ans, _fail, "jury");
    Claim participant = readClaim(ouf, _wa, "participant");

    if (participant.diameter > jury.diameter) {
        quitf(_wa, "participant diameter %d is worse than jury diameter %d",
              participant.diameter, jury.diameter);
    }
    if (participant.diameter < jury.diameter) {
        quitf(_fail, "participant diameter %d is better than jury diameter %d",
              participant.diameter, jury.diameter);
    }
    quitf(_ok, "diameter %d", participant.diameter);
}

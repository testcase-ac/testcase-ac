#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

int n;
vector<int> d;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int size) : parent(size + 1) {
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
        parent[b] = a;
        return true;
    }
};

struct Edge {
    int u;
    int v;
    int l;
    int r;
};

struct Claim {
    bool impossible;
};

static void invalid(InStream& stream, TResult verdict, const char* message) {
    stream.quitf(verdict, "%s", message);
}

static bool hasCrossing(vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        if (a.l != b.l) {
            return a.l < b.l;
        }
        return a.r < b.r;
    });

    multiset<int> activeRights;
    for (int i = 0; i < (int)edges.size();) {
        int currentLeft = edges[i].l;
        while (!activeRights.empty() && *activeRights.begin() <= currentLeft) {
            activeRights.erase(activeRights.begin());
        }

        int j = i;
        while (j < (int)edges.size() && edges[j].l == currentLeft) {
            if (!activeRights.empty() && *activeRights.begin() < edges[j].r) {
                return true;
            }
            ++j;
        }
        for (int k = i; k < j; ++k) {
            activeRights.insert(edges[k].r);
        }
        i = j;
    }

    return false;
}

static Claim readClaim(InStream& stream, TResult invalidVerdict, const char* role) {
    int first = stream.readInt(-1, n, format("%s first token", role).c_str());

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true};
    }
    if (first == 0) {
        stream.quitf(invalidVerdict, "%s first vertex is 0", role);
    }

    vector<Edge> edges;
    edges.reserve(n - 1);
    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> seen;
    Dsu dsu(n);

    int second = stream.readInt(1, n, format("%s edge[1].v", role).c_str());
    stream.readEoln();
    edges.push_back({first, second, min(first, second), max(first, second)});

    for (int i = 2; i <= n - 1; ++i) {
        int u = stream.readInt(1, n, format("%s edge[%d].u", role, i).c_str());
        int v = stream.readInt(1, n, format("%s edge[%d].v", role, i).c_str());
        stream.readEoln();
        edges.push_back({u, v, min(u, v), max(u, v)});
    }
    stream.readEof();

    for (int i = 0; i < n - 1; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (u == v) {
            stream.quitf(invalidVerdict, "%s edge[%d] is a self-loop at vertex %d", role, i + 1, u);
        }
        pair<int, int> normalized = {min(u, v), max(u, v)};
        if (!seen.insert(normalized).second) {
            stream.quitf(invalidVerdict,
                         "%s edge[%d] duplicates edge (%d, %d)",
                         role,
                         i + 1,
                         normalized.first,
                         normalized.second);
        }
        if (!dsu.unite(u, v)) {
            stream.quitf(invalidVerdict, "%s edge[%d] creates a cycle", role, i + 1);
        }
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int component = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        if (dsu.find(v) != component) {
            stream.quitf(invalidVerdict, "%s graph is disconnected at vertex %d", role, v);
        }
    }

    if (hasCrossing(edges)) {
        invalid(stream, invalidVerdict, format("%s graph has crossing edges", role).c_str());
    }

    int root = -1;
    for (int i = 1; i <= n; ++i) {
        if (d[i] == 0) {
            if (root != -1) {
                stream.quitf(invalidVerdict,
                             "%s cannot choose one root because d[%d] and d[%d] are both 0",
                             role,
                             root,
                             i);
            }
            root = i;
        }
    }
    if (root == -1) {
        invalid(stream, invalidVerdict, format("%s supplies a tree but input has no root with distance 0", role).c_str());
    }

    vector<int> dist(n + 1, -1);
    vector<int> queue;
    queue.reserve(n);
    dist[root] = 0;
    queue.push_back(root);
    for (int head = 0; head < (int)queue.size(); ++head) {
        int u = queue[head];
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue.push_back(v);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (dist[i] != d[i]) {
            stream.quitf(invalidVerdict,
                         "%s distance to vertex %d is %d, expected %d",
                         role,
                         i,
                         dist[i],
                         d[i]);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    d.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        d[i] = inf.readInt();
    }

    Claim jury = readClaim(ans, _fail, "jury");
    Claim participant = readClaim(ouf, _wa, "participant");

    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid tree while jury says -1");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "participant says -1 but jury supplies a valid tree");
    }

    quitf(_ok, "accepted");
}

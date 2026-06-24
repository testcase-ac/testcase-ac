#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

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

struct Edge {
    int u;
    int v;
    long long w;
};

struct Claim {
    bool possible;
    long long weight;
};

int n, m;
vector<Edge> edges;
long long minTreeWeight;
long long maxTreeWeight;

long long spanningTreeWeight(bool maximum) {
    vector<int> order(m);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (maximum) {
            return edges[a].w > edges[b].w;
        }
        return edges[a].w < edges[b].w;
    });

    Dsu dsu(n);
    long long total = 0;
    int used = 0;
    for (int id : order) {
        const Edge& edge = edges[id];
        if (dsu.unite(edge.u, edge.v)) {
            total += edge.w;
            ++used;
        }
    }

    if (used != n - 1) {
        quitf(_fail, "input graph has no spanning tree");
    }
    return total;
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, 0};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    Dsu dsu(n);
    vector<char> usedEdge(m + 1, false);
    long long total = 0;
    for (int i = 0; i < n - 1; ++i) {
        int id = stream.readInt(1, m, format("edge[%d]", i + 1).c_str());
        if (usedEdge[id]) {
            stream.quitf(_wa, "edge id %d is repeated", id);
        }
        usedEdge[id] = true;

        const Edge& edge = edges[id];
        if (!dsu.unite(edge.u, edge.v)) {
            stream.quitf(_wa, "edge id %d creates a cycle", id);
        }
        total += edge.w;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after selected edges");
    }

    if (n >= 1) {
        int root = dsu.find(1);
        for (int vertex = 2; vertex <= n; ++vertex) {
            if (dsu.find(vertex) != root) {
                stream.quitf(_wa, "selected edges do not connect vertex %d to vertex 1", vertex);
            }
        }
    }

    if (total == minTreeWeight) {
        stream.quitf(_wa, "selected tree is a minimum spanning tree with weight %lld", total);
    }
    if (total == maxTreeWeight) {
        stream.quitf(_wa, "selected tree is a maximum spanning tree with weight %lld", total);
    }

    return {true, total};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.assign(m + 1, {});
    for (int i = 1; i <= m; ++i) {
        edges[i].u = inf.readInt();
        edges[i].v = inf.readInt();
        edges[i].w = inf.readLong();
    }

    minTreeWeight = spanningTreeWeight(false);
    maxTreeWeight = spanningTreeWeight(true);

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.possible) {
        if (participant.possible) {
            quitf(_fail, "participant found a valid MMST with weight %lld while jury says NO", participant.weight);
        }
        quitf(_ok, "both outputs report NO");
    }

    if (!participant.possible) {
        quitf(_wa, "participant reports NO while jury provides a valid MMST");
    }

    quitf(_ok, "valid MMST with weight %lld", participant.weight);
}

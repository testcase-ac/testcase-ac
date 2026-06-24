#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

struct Answer {
    long long claimed;
    long long actual;
};

int n;

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(1, 10000000000LL, "distance sum");
    stream.readEoln();
    vector<vector<int>> graph(n + 1);
    DSU dsu(n);

    for (int i = 0; i < n - 1; ++i) {
        int u = stream.readInt(1, n, format("edge[%d].u", i + 1).c_str());
        int v = stream.readInt(1, n, format("edge[%d].v", i + 1).c_str());
        stream.readEoln();
        if (u == v) {
            stream.quitf(_wa, "edge %d is a self-loop at vertex %d", i + 1, u);
        }
        if (!dsu.unite(u, v)) {
            stream.quitf(_wa, "edge %d creates a cycle between %d and %d", i + 1, u, v);
        }
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    stream.readEof();

    int root = dsu.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        if (dsu.find(vertex) != root) {
            stream.quitf(_wa, "output graph is disconnected");
        }
    }

    long long actual = 0;
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.reserve(n);
    order.push_back(1);
    parent[1] = -1;

    for (int idx = 0; idx < (int)order.size(); ++idx) {
        int u = order[idx];
        for (int v : graph[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            order.push_back(v);
        }
    }

    vector<int> subtree(n + 1, 1);
    for (int idx = n - 1; idx > 0; --idx) {
        int u = order[idx];
        actual += 1LL * subtree[u] * (n - subtree[u]);
        subtree[parent[u]] += subtree[u];
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed distance sum %lld does not match tree distance sum %lld", claimed, actual);
    }

    return {claimed, actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 100000, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actual < jury.actual) {
        quitf(_fail, "participant found better tree: jury=%lld participant=%lld", jury.actual, participant.actual);
    }
    if (participant.actual > jury.actual) {
        quitf(_wa, "jury has better tree: jury=%lld participant=%lld", jury.actual, participant.actual);
    }

    quitf(_ok, "distance sum %lld", participant.actual);
}

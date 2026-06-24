#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), rank(n + 1, 0) {
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
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        return true;
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int n, m;
vector<Edge> edges;

long long minimumSpanningTreeWeight() {
    vector<int> order(m);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [](int a, int b) {
        if (edges[a].w != edges[b].w) {
            return edges[a].w < edges[b].w;
        }
        return a < b;
    });

    Dsu dsu(n);
    long long total = 0;
    int used = 0;
    for (int id : order) {
        if (dsu.unite(edges[id].u, edges[id].v)) {
            total += edges[id].w;
            ++used;
        }
    }
    if (used != n - 1) {
        quitf(_fail, "input graph is disconnected");
    }
    return total;
}

bool isSpanningTree(const vector<char>& inTree) {
    Dsu dsu(n);
    int used = 0;
    for (int id = 1; id <= m; ++id) {
        if (!inTree[id]) {
            continue;
        }
        ++used;
        if (!dsu.unite(edges[id].u, edges[id].v)) {
            return false;
        }
    }
    if (used != n - 1) {
        return false;
    }
    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        if (dsu.find(v) != root) {
            return false;
        }
    }
    return true;
}

long long treeWeight(const vector<char>& inTree) {
    long long total = 0;
    for (int id = 1; id <= m; ++id) {
        if (inTree[id]) {
            total += edges[id].w;
        }
    }
    return total;
}

struct Answer {
    int swaps;
    long long finalWeight;
};

Answer readAnswer(InStream& stream, long long mstWeight) {
    int swaps = stream.readInt(0, n - 1, "k");

    vector<char> inTree(m + 1, false);
    for (int id = 1; id <= n - 1; ++id) {
        inTree[id] = true;
    }

    for (int i = 0; i < swaps; ++i) {
        int removeId = stream.readInt(1, m, format("remove[%d]", i + 1).c_str());
        int addId = stream.readInt(1, m, format("add[%d]", i + 1).c_str());

        if (!inTree[removeId]) {
            stream.quitf(_wa,
                         "swap %d removes edge %d, which is not currently in the tree",
                         i + 1,
                         removeId);
        }
        if (inTree[addId]) {
            stream.quitf(_wa,
                         "swap %d adds edge %d, which is already in the tree",
                         i + 1,
                         addId);
        }

        inTree[removeId] = false;
        inTree[addId] = true;
        if (!isSpanningTree(inTree)) {
            stream.quitf(_wa, "swap %d does not leave a spanning tree", i + 1);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after swap list");
    }

    long long finalWeight = treeWeight(inTree);
    if (finalWeight != mstWeight) {
        stream.quitf(_wa,
                     "final tree weight is %lld, expected MST weight %lld",
                     finalWeight,
                     mstWeight);
    }
    return {swaps, finalWeight};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.assign(m + 1, Edge{});
    for (int id = 1; id <= m; ++id) {
        edges[id].u = inf.readInt();
        edges[id].v = inf.readInt();
        edges[id].w = inf.readLong();
    }

    long long mstWeight = minimumSpanningTreeWeight();
    Answer jury = readAnswer(ans, mstWeight);
    Answer participant = readAnswer(ouf, mstWeight);

    if (participant.swaps < jury.swaps) {
        quitf(_fail,
              "participant found fewer swaps than jury: participant=%d jury=%d",
              participant.swaps,
              jury.swaps);
    }
    if (participant.swaps > jury.swaps) {
        quitf(_wa, "expected %d swaps, found %d", jury.swaps, participant.swaps);
    }
    quitf(_ok, "answer uses %d swaps and final MST weight is %lld", participant.swaps, participant.finalWeight);
}

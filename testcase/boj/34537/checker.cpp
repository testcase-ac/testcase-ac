#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
    long long x;
    long long y;
};

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
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

struct Answer {
    long long claimed;
    long long achieved;
    long long cost;
};

int n, m;
long long budget;
vector<Edge> edges;

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(1, 1000000000000000LL, "X");
    vector<long long> times(m);
    long long totalCost = 0;

    for (int i = 0; i < m; ++i) {
        times[i] = stream.readLong(0, budget, format("upgrade[%d]", i + 1));
        if (times[i] > (budget - totalCost) / edges[i].y) {
            stream.quitf(_wa,
                         "upgrade plan exceeds budget at bridge %d: current cost %lld, add %lld * %lld, budget %lld",
                         i + 1,
                         totalCost,
                         times[i],
                         edges[i].y,
                         budget);
        }
        totalCost += times[i] * edges[i].y;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after upgrade plan");
    }

    vector<pair<long long, int>> byCapacity;
    byCapacity.reserve(m);
    for (int i = 0; i < m; ++i) {
        long long capacity = edges[i].w + times[i] * edges[i].x;
        byCapacity.push_back({capacity, i});
    }
    sort(byCapacity.begin(), byCapacity.end(), greater<pair<long long, int>>());

    Dsu dsu(n);
    int used = 0;
    long long achieved = 0;
    for (const auto& [capacity, index] : byCapacity) {
        if (!dsu.unite(edges[index].u, edges[index].v)) {
            continue;
        }
        ++used;
        achieved = capacity;
        if (used == n - 1) {
            break;
        }
    }

    if (used != n - 1) {
        stream.quitf(_fail, "input graph is disconnected");
    }
    if (claimed != achieved) {
        stream.quitf(_wa, "claimed X is %lld, but the supplied upgrade plan achieves %lld", claimed, achieved);
    }

    return {claimed, achieved, totalCost};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    budget = inf.readLong();
    edges.resize(m);

    for (int i = 0; i < m; ++i) {
        edges[i].u = inf.readInt();
        edges[i].v = inf.readInt();
        edges[i].w = inf.readLong();
        edges[i].x = inf.readLong();
        edges[i].y = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.achieved < jury.achieved) {
        quitf(_wa,
              "jury has better answer: jury=%lld participant=%lld",
              jury.achieved,
              participant.achieved);
    }
    if (participant.achieved > jury.achieved) {
        quitf(_fail,
              "participant found better answer: jury=%lld participant=%lld",
              jury.achieved,
              participant.achieved);
    }

    quitf(_ok, "answer=%lld cost=%lld", participant.achieved, participant.cost);
}

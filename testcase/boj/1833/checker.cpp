#include "testlib.h"
#include <numeric>
#include <set>
#include <vector>
using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int n;
long long installedCost;
vector<vector<int>> cost;

struct Answer {
    long long totalCost;
    int addedCount;
};

Answer readAnswer(InStream& stream) {
    long long claimedCost = stream.readLong(0, 400000000LL, "C");
    int m = stream.readInt(0, n * (n - 1) / 2, "M");
    stream.readEoln();

    Dsu dsu(n);
    long long computedCost = installedCost;
    set<pair<int, int>> added;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (cost[i][j] < 0) {
                dsu.unite(i, j);
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        int a = stream.readInt(1, n, format("edge[%d].u", i + 1).c_str()) - 1;
        int b = stream.readInt(1, n, format("edge[%d].v", i + 1).c_str()) - 1;
        stream.readEoln();

        if (a == b) {
            stream.quitf(_wa, "edge %d connects city %d to itself", i + 1, a + 1);
        }
        if (a > b) {
            swap(a, b);
        }
        if (cost[a][b] < 0) {
            stream.quitf(_wa, "edge %d (%d, %d) is already installed", i + 1, a + 1, b + 1);
        }
        if (!added.insert({a, b}).second) {
            stream.quitf(_wa, "edge %d (%d, %d) is duplicated", i + 1, a + 1, b + 1);
        }

        computedCost += cost[a][b];
        dsu.unite(a, b);
    }

    stream.readEof();

    for (int i = 1; i < n; ++i) {
        if (dsu.find(i) != dsu.find(0)) {
            stream.quitf(_wa, "output railway network is disconnected");
        }
    }
    if (claimedCost != computedCost) {
        stream.quitf(
            _wa,
            "claimed cost %lld does not match computed cost %lld",
            claimedCost,
            computedCost
        );
    }

    return {computedCost, m};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    cost.assign(n, vector<int>(n));
    installedCost = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cost[i][j] = inf.readInt();
            if (i < j && cost[i][j] < 0) {
                installedCost += -cost[i][j];
            }
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.totalCost > jury.totalCost) {
        quitf(
            _wa,
            "jury has better total cost: jury=%lld participant=%lld",
            jury.totalCost,
            participant.totalCost
        );
    }
    if (participant.totalCost < jury.totalCost) {
        quitf(
            _fail,
            "participant found better total cost: jury=%lld participant=%lld",
            jury.totalCost,
            participant.totalCost
        );
    }
    quitf(_ok, "total cost %lld with %d added edges", participant.totalCost, participant.addedCount);
}

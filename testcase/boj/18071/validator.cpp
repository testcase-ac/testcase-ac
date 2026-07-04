#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent_(n + 1), size_(n + 1, 1) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size_[a] < size_[b]) {
            swap(a, b);
        }
        parent_[b] = a;
        size_[a] += size_[b];
        return true;
    }

private:
    vector<int> parent_;
    vector<int> size_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int u = inf.readInt(1, n, "u_i");
        inf.readEoln();

        ensuref(v != u, "self-loop at edge %d: %d %d", i, v, u);
        auto edge = minmax(v, u);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: %d %d", i, v, u);
        ensuref(dsu.unite(v, u),
                "cycle introduced at edge %d: %d %d", i, v, u);
    }

    for (int city = 2; city <= n; ++city) {
        ensuref(dsu.find(city) == dsu.find(1),
                "tree is disconnected: city %d is not connected to city 1", city);
    }

    vector<int> teams = inf.readInts(m, 1, n, "c_i");
    inf.readEoln();
    set<int> distinctTeams(teams.begin(), teams.end());
    ensuref(static_cast<int>(distinctTeams.size()) == m,
            "team cities must be different");

    inf.readEof();
}

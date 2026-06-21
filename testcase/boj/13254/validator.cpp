#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent_(n), size_(n, 1) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int Find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }

    bool Unite(int a, int b) {
        a = Find(a);
        b = Find(b);
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

    int n = inf.readInt(2, 51, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50, "M");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        int a = inf.readInt(0, n - 1, "edge_u");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "edge_v");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i + 1, a, b);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d",
                i + 1, a, b);
        dsu.Unite(a, b);
    }

    int root = dsu.Find(0);
    for (int city = 1; city < n; ++city) {
        ensuref(dsu.Find(city) == root, "road network is not connected");
    }

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, n - 1, "family_city");
    }
    inf.readEoln();

    inf.readEof();
}

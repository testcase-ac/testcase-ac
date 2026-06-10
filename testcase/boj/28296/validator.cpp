#include "testlib.h"

#include <algorithm>
#include <numeric>
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

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size_[a] < size_[b]) {
            swap(a, b);
        }
        parent_[b] = a;
        size_[a] += size_[b];
    }

private:
    vector<int> parent_;
    vector<int> size_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, min(n / 2, 50000), "K");
    inf.readSpace();
    int m = inf.readInt(n - 1, 300000, "M");
    inf.readEoln();

    vector<int> companyCount(k + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int company = inf.readInt(1, k, "C_i");
        ++companyCount[company];
        if (i < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    for (int company = 1; company <= k; ++company) {
        ensuref(companyCount[company] >= 2,
                "company %d owns only %d warehouses", company, companyCount[company]);
    }

    Dsu dsu(n);
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "X");
        inf.readSpace();
        int y = inf.readInt(1, n, "Y");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "W");
        inf.readEoln();

        // CHECK: Multiple roads are explicitly allowed, but a road connecting
        // two warehouses is treated as having distinct endpoints.
        ensuref(x != y, "self-loop road at edge %d: %d %d", i, x, y);
        dsu.unite(x, y);
    }

    int root = dsu.find(1);
    for (int warehouse = 2; warehouse <= n; ++warehouse) {
        ensuref(dsu.find(warehouse) == root,
                "graph is disconnected: warehouse %d is not reachable from warehouse 1",
                warehouse);
    }

    inf.readEof();
}

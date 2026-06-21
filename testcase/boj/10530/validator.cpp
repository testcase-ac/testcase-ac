#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent_(n), size_(n, 1) {
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

    int p = inf.readInt(2, 10000, "P");
    inf.readSpace();
    int t = inf.readInt(1, 250000, "T");
    inf.readEoln();

    Dsu dsu(p);
    for (int i = 0; i < t; ++i) {
        int p1 = inf.readInt(0, p - 1, "p1");
        inf.readSpace();
        int p2 = inf.readInt(0, p - 1, "p2");
        inf.readSpace();
        inf.readInt(1, 1000, "l");
        inf.readEoln();

        dsu.unite(p1, p2);
    }

    ensuref(dsu.find(0) == dsu.find(p - 1),
            "there must be a path from entrance 0 to highest peak %d", p - 1);

    inf.readEof();
}

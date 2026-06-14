#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
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

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int w = inf.readInt(1, 99, "W");
    inf.readSpace();
    int p = inf.readInt(1, 10000, "P");
    inf.readEoln();

    ensuref(w == n - 1, "exactly one path between every pair requires W = N - 1, got N=%d W=%d", n, w);

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= w; ++i) {
        int a = inf.readInt(1, n, "wire_u");
        inf.readSpace();
        int b = inf.readInt(1, n, "wire_v");
        inf.readSpace();
        inf.readInt(1, 500, "wire_time");
        inf.readEoln();

        ensuref(a != b, "wire %d is a loop at computer %d", i, a);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "wire %d duplicates edge (%d, %d)", i, edge.first, edge.second);
        ensuref(dsu.unite(a, b), "wire %d creates a cycle between %d and %d", i, a, b);
    }

    int root = dsu.find(1);
    for (int computer = 2; computer <= n; ++computer) {
        ensuref(dsu.find(computer) == root, "computer %d is not connected to computer 1", computer);
    }

    for (int i = 1; i <= p; ++i) {
        int source = inf.readInt(1, n, "packet_source");
        inf.readSpace();
        int destination = inf.readInt(1, n, "packet_destination");
        inf.readEoln();

        ensuref(source != destination, "packet %d has identical source and destination %d", i, source);
    }

    inf.readEof();
}

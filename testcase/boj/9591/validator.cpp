#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readSpace();
    int m = inf.readInt(max(0, n - 1), 1000, "M");
    inf.readEoln();

    vector<int> floor(n);
    for (int i = 0; i < n; ++i) {
        // CHECK: The statement gives no coordinate or floor range. Keep all
        // positions nonnegative and within a practical map-size cap.
        floor[i] = inf.readInt(0, 1000000, "floor_i");
        inf.readSpace();
        inf.readInt(0, 1000000, "x_i");
        inf.readSpace();
        inf.readInt(0, 1000000, "y_i");
        inf.readEoln();
    }

    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);
    auto findRoot = [&](int v) {
        while (parent[v] != v) {
            parent[v] = parent[parent[v]];
            v = parent[v];
        }
        return v;
    };
    auto unite = [&](int a, int b) {
        a = findRoot(a);
        b = findRoot(b);
        if (a != b) {
            parent[b] = a;
        }
    };

    set<pair<int, int>> seenEdges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n - 1, "u_i");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "v_i");
        inf.readSpace();
        string type = inf.readToken("walking|stairs|lift|escalator", "type_i");
        inf.readEoln();

        // CHECK: A connection between two places is interpreted as a real edge,
        // so loops and duplicate undirected edges are rejected.
        ensuref(a != b, "loop at connection %d: %d", i + 1, a);
        ensuref(seenEdges.insert(minmax(a, b)).second,
                "duplicate connection at index %d: %d %d", i + 1, a, b);
        // CHECK: The statement says the type for places in the same floor is
        // walking; interpret this as exactly the valid same-floor movement.
        ensuref((floor[a] == floor[b]) == (type == "walking"),
                "connection %d has type %s for floors %d and %d", i + 1,
                type.c_str(), floor[a], floor[b]);
        unite(a, b);
    }

    int root = findRoot(0);
    for (int i = 1; i < n; ++i) {
        ensuref(findRoot(i) == root, "place %d is not connected to place 0", i);
    }

    int q = inf.readInt(1, 1000, "Q");
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        inf.readInt(0, n - 1, "a_i");
        inf.readSpace();
        inf.readInt(0, n - 1, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}

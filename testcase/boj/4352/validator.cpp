#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

class DSU {
public:
    explicit DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) ++rank[a];
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int tc = 1;; ++tc) {
        int n = inf.readInt(0, 15, "n");
        if (n == 0) {
            inf.readEoln();
            inf.readEof();
            return 0;
        }

        setTestCase(tc);

        inf.readSpace();
        int m = inf.readInt(1, 999, "m");
        inf.readEoln();

        DSU dsu(n + 1);
        vector<int> incident(n + 1, 0);

        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readSpace();
            // CHECK: The statement only says trail lengths are positive integers; cap them to a practical int-sized range.
            inf.readInt(1, 1000000, "length");
            inf.readEoln();

            dsu.unite(a, b);
            ++incident[a];
            ++incident[b];
        }

        int component = -1;
        for (int v = 1; v <= n; ++v) {
            if (incident[v] == 0) continue;
            int root = dsu.find(v);
            if (component == -1) {
                component = root;
            } else {
                ensuref(root == component,
                        "case %d has trails in disconnected components", tc);
            }
        }
    }
}

#include "testlib.h"
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = findRoot(parent, parent[x]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int dataset = 1;; ++dataset) {
        int n = inf.readInt(0, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 10000, "m");
        inf.readEoln();

        if (n == 0 && m == 0) break;

        setTestCase(dataset);
        ensuref(n >= 2, "n must be at least 2");
        ensuref(n % 2 == 0, "n must be even");
        ensuref(m >= n - 1, "m must be at least n - 1");

        vector<int> parent(n + 1);
        iota(parent.begin(), parent.end(), 0);

        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int s = inf.readInt(1, n, "s_i");
            inf.readSpace();
            // CHECK: The statement text says t_i <= s_i, but the official
            // sample contains edge "1 2 5", so endpoint order is unrestricted.
            int t = inf.readInt(1, n, "t_i");
            inf.readSpace();
            inf.readInt(1, 1000, "c_i");
            inf.readEoln();

            ensuref(s != t, "self-loop at edge %d: %d", i, s);
            auto edge = minmax(s, t);
            ensuref(edges.insert(edge).second,
                    "duplicate undirected edge at edge %d: (%d, %d)", i, s, t);

            int rs = findRoot(parent, s);
            int rt = findRoot(parent, t);
            if (rs != rt) parent[rt] = rs;
        }

        int root = findRoot(parent, 1);
        for (int v = 2; v <= n; ++v) {
            ensuref(findRoot(parent, v) == root,
                    "graph is not connected; node %d is disconnected", v);
        }
    }

    inf.readEof();
}

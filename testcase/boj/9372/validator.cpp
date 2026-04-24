#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, r;
    int comp;
    DSU(int n) : p(n+1), r(n+1, 0), comp(n) {
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        --comp;
        return true;
    }
    int components() const {
        return comp;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N and M
        int N = inf.readInt(2, 1000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 10000, "M");
        inf.readEoln();

        // Prepare DSU to check connectivity
        DSU dsu(N);

        for (int i = 0; i < M; ++i) {
            int a = inf.readInt(1, N, "a");
            inf.readSpace();
            int b = inf.readInt(1, N, "b");
            inf.readEoln();

            ensuref(a != b,
                    "Loop detected at test case %d, edge index %d: (%d, %d)",
                    tc, i, a, b);

            dsu.unite(a, b);
        }

        // Check connectivity
        int comps = dsu.components();
        ensuref(comps == 1,
                "Graph is disconnected in test case %d: %d components found",
                tc, comps);
    }

    inf.readEof();
    return 0;
}

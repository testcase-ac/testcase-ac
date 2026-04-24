#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    vector<int> p;
    int comps;
    DSU(int n): p(n, -1), comps(n) {}
    int find(int x) {
        return p[x] < 0 ? x : (p[x] = find(p[x]));
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        --comps;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = 0;
    while (true) {
        // Read m, n (allow sentinel 0 0)
        int m = inf.readInt(0, 200000, "m");
        inf.readSpace();
        int n = inf.readInt(0, 200000, "n");
        inf.readEoln();

        // Sentinel check
        if (m == 0 && n == 0) break;

        // New test case
        ++T;
        setTestCase(T);
        ensuref(T <= 100000, "Number of test cases exceeds 100000: %d", T);

        // Validate m and n
        ensuref(m >= 1, "m must be at least 1, found %d", m);
        ensuref(n >= m - 1 && n <= 200000,
                "n must satisfy m-1 <= n <= 200000, found n=%d, m=%d", n, m);

        // Prepare for edges and connectivity
        DSU dsu(m);
        long long sumz = 0;

        for (int i = 0; i < n; i++) {
            int x = inf.readInt(0, m - 1, "x_i");
            inf.readSpace();
            int y = inf.readInt(0, m - 1, "y_i");
            inf.readSpace();
            long long z = inf.readLong(0LL, (1LL<<31) - 1, "z_i");
            inf.readEoln();

            ensuref(x != y, "Loop detected at edge %d: (%d, %d)", i, x, y);
            sumz += z;
            ensuref(sumz < (1LL<<31),
                    "Sum of distances must be less than 2^31, exceeded at edge %d: sum=%lld", i, sumz);

            dsu.unite(x, y);
        }

        // Connectivity check
        ensuref(dsu.comps == 1,
                "Graph is not connected, number of components: %d", dsu.comps);
    }

    inf.readEof();
    return 0;
}

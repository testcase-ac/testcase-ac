#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // Read employee data
    // salaries are in [1, 2^31-1]
    const long long SAL_MIN = 1LL;
    const long long SAL_MAX = 2147483647LL;
    vector<int> manager(N+1, 0);
    // i = 1: only salary
    long long sal1 = inf.readLong(SAL_MIN, SAL_MAX, "salary[1]");
    inf.readEoln();
    // i = 2..N: salary and manager
    for (int i = 2; i <= N; i++) {
        long long s = inf.readLong(SAL_MIN, SAL_MAX, "salary");
        inf.readSpace();
        int m = inf.readInt(1, N, "manager");
        inf.readEoln();
        manager[i] = m;
        // no self-loop
        ensuref(m != i, "Employee %d has self as manager", i);
    }

    // Validate tree structure: no cycles, all connected to 1
    DSU dsu(N);
    for (int i = 2; i <= N; i++) {
        int m = manager[i];
        // union; detect cycle if already connected
        if (!dsu.unite(i, m)) {
            ensuref(false, "Cycle detected at employee %d with manager %d", i, m);
        }
    }
    // Check connectivity: all must be in same comp as 1
    int root1 = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == root1, "Employee %d is not connected to root 1", i);
    }

    // Read queries
    for (int q = 0; q < M; q++) {
        // type: 'p' or 'u'
        string type = inf.readToken("p|u", "query_type");
        inf.readSpace();
        int a = inf.readInt(1, N, "a");
        if (type == "p") {
            inf.readSpace();
            int x = inf.readInt(-10000, 10000, "x");
            (void)x; // just for validator
        } else {
            // type == "u"
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

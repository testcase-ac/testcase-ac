#include "testlib.h"
#include <vector>
using namespace std;

// Simple DSU (Disjoint Set Union) for connectivity check
struct DSU {
    vector<int> p;
    DSU(int n) : p(n) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) p[b] = a;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and M
        int N = inf.readInt(1, 50000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 200000, "M");
        inf.readEoln();

        // Prepare DSU for nodes 1..N
        DSU dsu(N + 1);

        // Read edges
        for (int i = 0; i < M; i++) {
            int x = inf.readInt(1, N, "x");
            inf.readSpace();
            int y = inf.readInt(1, N, "y");
            inf.readSpace();
            // time t and garnet g: 32-bit signed positive integers
            long long t = inf.readLong(1LL, 2147483647LL, "t");
            inf.readSpace();
            long long g = inf.readLong(1LL, 2147483647LL, "g");
            inf.readEoln();

            // Union for connectivity
            dsu.unite(x, y);
        }

        // Ensure there's a path from 1 to N
        ensuref(dsu.find(1) == dsu.find(N),
                "Test case %d: no path between 1 and N (found disconnected)", tc);
    }

    inf.readEof();
    return 0;
}

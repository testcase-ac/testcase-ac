#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m, k
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 250000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    // Check the global constraint m * k <= 3e6
    long long prod = (long long)m * (long long)k;
    ensuref(prod <= 3000000LL,
            "Constraint violated: m * k must be <= 3e6, but m=%d, k=%d, m*k=%lld",
            m, k, prod);

    // Read edges and check constraints
    set<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000, "c_i");
        inf.readEoln();

        // No duplicate directed edges
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at index %d: (%d -> %d)", i, a, b);
        edges.insert({a, b});
    }

    inf.readEof();
    return 0;
}

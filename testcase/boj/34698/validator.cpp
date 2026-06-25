#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 20000, "M");
    inf.readEoln();

    // CHECK: The statement does not forbid repeated directed edges.
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "edge_a");
        inf.readSpace();
        int b = inf.readInt(1, n, "edge_b");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d -> %d", i + 1, a, b);
    }

    int q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    int totalK = 0;
    for (int qi = 0; qi < q; ++qi) {
        setTestCase(qi + 1);

        int a = inf.readInt(1, n, "query_a");
        inf.readSpace();
        int b = inf.readInt(1, n, "query_b");
        inf.readSpace();
        int k = inf.readInt(0, n - 2, "k");
        totalK += k;
        ensuref(totalK <= 100000, "sum of k exceeds 100000 at query %d", qi + 1);

        set<int> used;
        used.insert(a);
        used.insert(b);

        if (k > 0) {
            ensuref(a != b, "query %d has k > 0 but a and b are equal: %d", qi + 1, a);
        }

        for (int i = 0; i < k; ++i) {
            inf.readSpace();
            int p = inf.readInt(1, n, "p_i");
            ensuref(used.insert(p).second,
                    "query %d has duplicate among a, b, and p_%d: %d", qi + 1, i + 1, p);
        }

        inf.readEoln();
    }

    inf.readEof();
}

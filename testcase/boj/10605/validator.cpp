#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    int totalRecords = 0;

    while (true) {
        int n = inf.readInt(0, 300, "n");
        inf.readSpace();
        int m = inf.readInt(0, 300 * 299 / 2, "m");
        inf.readSpace();
        int k = inf.readInt(0, 1000, "k");
        inf.readEoln();

        if (n == 0 && m == 0 && k == 0) {
            break;
        }

        ++tc;
        setTestCase(tc);

        ensuref(1 <= n, "n must be positive in a non-terminal test case");
        ensuref(1 <= k, "k must be positive in a non-terminal test case");
        // CHECK: The Korean text gives M <= N(N-1), but the English original
        // and simple undirected-road wording imply at most one road per pair.
        ensuref(m <= n * (n - 1) / 2, "too many roads for n=%d: m=%d", n, m);

        totalRecords += m + k;
        // CHECK: The statement gives no number-of-test-cases cap; keep the
        // total input size below the local scalar-token practical limit.
        ensuref(totalRecords <= 1000000, "too many road/dragon records");

        set<pair<int, int>> roads;
        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readEoln();

            ensuref(a != b, "self-loop road %d: (%d, %d)", i, a, b);
            auto road = minmax(a, b);
            ensuref(roads.insert(road).second,
                    "duplicate road %d: (%d, %d)", i, a, b);
        }

        for (int i = 1; i <= k; ++i) {
            inf.readInt(1, n, "c");
            inf.readSpace();
            inf.readInt(1, 100000, "s");
            inf.readSpace();
            inf.readInt(0, 100000, "heads_grown");
            inf.readEoln();
        }
    }

    ensuref(tc <= 100000, "too many test cases: %d", tc);
    inf.readEof();
}

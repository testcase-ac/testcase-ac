#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int dataset = 0;
    while (true) {
        int n = inf.readInt(0, 100, "n");
        inf.readSpace();
        int m = inf.readInt(0, 4950, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ++dataset;
        setTestCase(dataset);
        ensuref(2 <= n && n <= 100, "n must be in [2, 100], got %d", n);
        ensuref(m <= n * (n - 1) / 2,
                "m must be at most n(n-1)/2, got n=%d m=%d", n, m);

        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, n, "b_i");
            inf.readSpace();
            int w = inf.readInt(1, 10000, "w_i");
            inf.readEoln();

            ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);
            auto edge = minmax(a, b);
            ensuref(edges.insert(edge).second,
                    "parallel edge at edge %d: %d %d", i, a, b);
        }
    }

    inf.readEof();
}

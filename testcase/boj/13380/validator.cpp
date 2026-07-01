#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 5, "K");
    inf.readEoln();

    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 10, "N");
        inf.readSpace();
        int m = inf.readInt(1, 50, "M");
        inf.readSpace();
        inf.readLong(1LL, 1000000000000LL, "T");
        inf.readEoln();

        ensuref(m <= n * (n - 1) / 2,
                "M=%d exceeds the number of distinct unordered pairs for N=%d",
                m, n);

        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(1, n, "B");
            inf.readEoln();

            ensuref(a != b, "loop at edge %d: (%d, %d)", i, a, b);
            auto edge = minmax(a, b);
            ensuref(edges.insert(edge).second,
                    "duplicate road at edge %d: (%d, %d)", i, a, b);
        }
    }

    inf.readEof();
}

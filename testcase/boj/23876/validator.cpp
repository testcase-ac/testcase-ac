#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    long long totalNM = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int m = inf.readInt(0, 100000, "M");
        inf.readEoln();

        totalNM += static_cast<long long>(n) + m;
        ensuref(totalNM <= 500000, "sum of N+M exceeds 500000 at case %d", tc);

        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "i");
            inf.readSpace();
            int b = inf.readInt(1, n, "j");
            inf.readEoln();

            ensuref(a != b, "edge %d is a self-loop: %d %d", i, a, b);
            auto edge = minmax(a, b);
            ensuref(edges.insert(edge).second, "duplicate edge %d: %d %d", i, a, b);
        }
    }

    inf.readEof();
}

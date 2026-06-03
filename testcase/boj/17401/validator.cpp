#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readSpace();
    int n = inf.readInt(2, 20, "N");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "D");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        set<pair<int, int>> edges;

        int m = inf.readInt(0, n * n, "M_i");
        inf.readEoln();

        for (int j = 1; j <= m; ++j) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readSpace();
            inf.readInt(1, 1000, "c");
            inf.readEoln();

            ensuref(edges.insert({a, b}).second,
                    "duplicate edge relation in map %d at entry %d: %d -> %d",
                    i, j, a, b);
        }
    }

    inf.readEof();
}

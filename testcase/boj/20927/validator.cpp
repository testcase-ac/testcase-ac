#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    int m = inf.readInt(0, 27, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, n - 1, "b_i");
    }
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readSpace();
        inf.readInt(-1000000, 1000000, "C");
        inf.readEoln();

        ensuref(a < b, "edge %d must satisfy A < B, got %d %d", i, a, b);
        ensuref(edges.insert({a, b}).second,
                "duplicate edge pair at edge %d: %d %d", i, a, b);
    }

    inf.readEof();
}

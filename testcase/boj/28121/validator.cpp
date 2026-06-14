#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 600000, "Q");
    inf.readEoln();

    long long possibleEdges = 1LL * n * (n - 1) / 2;
    ensuref(q <= possibleEdges,
            "Q=%d exceeds the number of possible distinct edges for N=%d", q, n);

    set<pair<int, int>> edges;
    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n - 1, "a_i");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "b_i");
        inf.readEoln();

        ensuref(edges.insert({a, b}).second,
                "duplicate query at index %d: (%d, %d)", i, a, b);
    }

    inf.readEof();
}

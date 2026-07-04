#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, min(300000LL, 1LL * n * (n - 1) / 2), "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a < b, "edge index %d must satisfy a_i < b_i: (%d, %d)",
                i + 1, a, b);
        ensuref(edges.insert({a, b}).second,
                "duplicate edge at index %d: (%d, %d)", i + 1, a, b);
    }

    inf.readEof();
}

#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 40, "N");
    inf.readSpace();
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(1, maxM, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a < b, "edge %d must satisfy a_i < b_i, got %d %d", i, a, b);
        ensuref(edges.insert({a, b}).second,
                "duplicate edge at index %d: %d %d", i, a, b);
    }

    inf.readEof();
}

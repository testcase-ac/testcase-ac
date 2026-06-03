#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 100, "Q");
    inf.readEoln();

    set<pair<int, int>> met;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readEoln();

        ensuref(a != b, "initial pair %d uses the same cow %d", i, a);
        auto edge = minmax(a, b);
        ensuref(met.insert(edge).second,
                "initial pair %d repeats cows %d and %d", i, a, b);
    }

    for (int j = 1; j <= q; ++j) {
        int x = inf.readInt(1, n, "X_j");
        inf.readSpace();
        int y = inf.readInt(1, n, "Y_j");
        inf.readEoln();

        ensuref(x != y, "query %d uses the same cow %d", j, x);
    }

    inf.readEof();
}

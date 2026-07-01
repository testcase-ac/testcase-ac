#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400, "N");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1), "M");
    inf.readSpace();
    inf.readInt(1, 200, "X");
    inf.readSpace();
    inf.readInt(1, 200, "Y");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "self precedence pair at index %d: (%d, %d)", i + 1, a, b);
        ensuref(edges.insert({a, b}).second,
                "duplicate precedence pair at index %d: (%d, %d)", i + 1, a, b);
    }

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 200, "x_j");
        inf.readSpace();
        inf.readInt(1, 200, "y_j");
        inf.readEoln();
    }

    inf.readEof();
}

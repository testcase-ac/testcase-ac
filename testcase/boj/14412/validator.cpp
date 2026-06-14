#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(0, maxEdges - 1, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop: %d %d", i, a, b);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge %d: %d %d", i, a, b);
    }

    inf.readEof();
}

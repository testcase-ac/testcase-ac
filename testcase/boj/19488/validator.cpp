#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readSpace();
    int d = inf.readInt(1, n - 1, "d");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "road %d is a self-loop at city %d", i, a);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate road %d connects cities %d and %d", i, edge.first, edge.second);
    }

    inf.readEof();
}

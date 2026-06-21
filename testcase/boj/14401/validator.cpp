#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(0, 2000, "m");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000000, 1000000, "x");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y");
        inf.readEoln();

        ensuref(positions.insert({x, y}).second,
                "duplicate city position at index %d: (%d, %d)", i + 1, x, y);
    }

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        // CHECK: The statement gives only 1 <= a,b <= n, but roads connect two cities.
        ensuref(a != b, "self-loop at edge index %d: (%d, %d)", i + 1, a, b);

        // CHECK: Existing highways are treated as an undirected simple graph.
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate edge at index %d: (%d, %d)", i + 1, a, b);
    }

    inf.readEof();
}

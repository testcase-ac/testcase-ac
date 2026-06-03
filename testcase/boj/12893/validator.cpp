#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 1000000, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        // CHECK: "enemy relationship between A and B" is treated as two distinct people.
        ensuref(a != b, "self enemy relation at edge %d: %d", i + 1, a);

        // CHECK: M counts enemy relationships, so repeated unordered pairs are rejected.
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate enemy relation at edge %d: (%d, %d)", i + 1, a, b);
    }

    inf.readEof();
}

#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    inf.readInt(1, 10000000, "X");
    inf.readSpace();
    inf.readInt(0, n - 1, "Y");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(0, n - 1, "A");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "B");
        inf.readSpace();
        inf.readInt(1, 10000, "C");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at house %d", i, a);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate road at edge %d between houses %d and %d",
                i, edge.first, edge.second);
    }

    inf.readEof();
    return 0;
}

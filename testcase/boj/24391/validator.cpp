#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int edgeIndex = 1; edgeIndex <= m; ++edgeIndex) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readEoln();

        ensuref(i != j, "self-loop at edge %d: %d", edgeIndex, i);
        auto edge = minmax(i, j);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: (%d, %d)", edgeIndex, i, j);
    }

    vector<int> schedule = inf.readInts(n, 1, n, "A_i");
    inf.readEoln();
    inf.readEof();
}

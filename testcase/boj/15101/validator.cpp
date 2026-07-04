#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 10000, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    set<int> forcedStarts;

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(-n, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != 0, "edge %d has zero start node", i);

        int from = abs(a);
        ensuref(from != b, "edge %d is a self-loop: %d -> %d", i, from, b);
        ensuref(edges.insert({from, b}).second,
                "duplicate directed edge at edge %d: %d -> %d", i, from, b);

        if (a < 0) {
            ensuref(forcedStarts.insert(from).second,
                    "multiple forced moves start at node %d", from);
            ensuref(static_cast<int>(forcedStarts.size()) <= 900,
                    "more than 900 forced moves");
        }
    }

    inf.readEof();
}

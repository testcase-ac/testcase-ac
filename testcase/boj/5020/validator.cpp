#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, (3 * n) / 2, "m");
    inf.readEoln();

    vector<int> degree(n + 1, 0);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n - 1, "a_i");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "b_i");
        inf.readEoln();

        ensuref(edges.insert({a, b}).second,
                "duplicate enemy pair at line %d: %d %d", i + 1, a, b);

        ++degree[a];
        ++degree[b];
        ensuref(degree[a] <= 3, "soldier %d has more than 3 enemies", a);
        ensuref(degree[b] <= 3, "soldier %d has more than 3 enemies", b);
    }

    inf.readEof();
    return 0;
}

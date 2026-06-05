#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 250000, "m");
    inf.readEoln();

    set<pair<int, int>> reportedPairs;
    vector<bool> seen(n, false);

    for (int i = 0; i < m; ++i) {
        int k = inf.readInt(0, n - 1, "k");
        inf.readSpace();
        string symbol = inf.readToken("[=>]", "symbol");
        inf.readSpace();
        int l = inf.readInt(0, n - 1, "l");
        inf.readEoln();

        // CHECK: a reported chess match is between opponents, so self-matches are not valid reports.
        ensuref(k != l, "self-match at report %d: player %d", i + 1, k);

        pair<int, int> normalized = minmax(k, l);
        ensuref(reportedPairs.insert(normalized).second,
                "multiple reports for player pair at report %d: (%d, %d)", i + 1, k, l);

        seen[k] = true;
        seen[l] = true;
    }

    for (int player = 0; player < n; ++player) {
        ensuref(seen[player], "player %d does not take part in any reported match", player);
    }

    inf.readEof();
}

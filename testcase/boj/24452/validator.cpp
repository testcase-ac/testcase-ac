#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 400000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 400000, "M");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "U_i");
        inf.readSpace();
        int v = inf.readInt(u + 1, n, "V_i");
        inf.readEoln();

        ensuref(edges.insert({u, v}).second,
                "duplicate edge at index %d: (%d, %d)", i, u, v);
    }

    vector<bool> state_seen(k + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int s = inf.readInt(1, k, "S_j");
        state_seen[s] = true;
    }
    inf.readEoln();

    for (int state = 1; state <= k; ++state) {
        ensuref(state_seen[state], "state %d has no city", state);
    }

    int q = inf.readInt(1, 400000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "A_k");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_k");
        inf.readEoln();

        ensuref(a != b, "query %d has equal endpoints: %d", i, a);
    }

    inf.readEof();
}

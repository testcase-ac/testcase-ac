#include "testlib.h"

#include <vector>

using namespace std;

namespace {

bool hasCycleFrom(int v, const vector<vector<int>>& parents, vector<int>& state) {
    state[v] = 1;
    for (int parent : parents[v]) {
        if (state[parent] == 1) {
            return true;
        }
        if (state[parent] == 0 && hasCycleFrom(parent, parents, state)) {
            return true;
        }
    }
    state[v] = 2;
    return false;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        vector<vector<int>> parents(n);
        for (int i = 0; i < n; ++i) {
            int m = inf.readInt(0, 10, "M_i");
            vector<bool> seen(n, false);
            for (int j = 0; j < m; ++j) {
                inf.readSpace();
                int parent = inf.readInt(1, n, "parent");
                --parent;
                ensuref(parent != i, "class %d inherits from itself", i + 1);
                ensuref(!seen[parent], "duplicate parent %d for class %d", parent + 1, i + 1);
                seen[parent] = true;
                parents[i].push_back(parent);
            }
            inf.readEoln();
        }

        vector<int> state(n, 0);
        for (int i = 0; i < n; ++i) {
            ensuref(state[i] != 0 || !hasCycleFrom(i, parents, state),
                    "inheritance cycle reachable from class %d", i + 1);
        }
    }

    inf.readEof();
}

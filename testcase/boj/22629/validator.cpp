#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        parent[i] = inf.readInt(1, n, "p_i");
        inf.readEoln();
        ensuref(parent[i] != i, "node %d cannot be its own parent", i);
    }

    vector<int> state(n + 1, 0);
    state[1] = 2;
    for (int i = 2; i <= n; ++i) {
        if (state[i] == 2) {
            continue;
        }

        int current = i;
        while (state[current] == 0) {
            state[current] = 1;
            current = parent[current];
        }
        ensuref(state[current] == 2, "parent chain from node %d does not reach root", i);

        current = i;
        while (state[current] == 1) {
            state[current] = 2;
            current = parent[current];
        }
    }

    for (int i = 1; i <= q; ++i) {
        string op = inf.readToken("M|Q", "operation");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readEoln();
        (void)op;
    }

    inf.readEof();
}

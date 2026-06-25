#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    parent[1] = 1;

    for (int i = 2; i <= n; ++i) {
        int p = inf.readInt(1, n, "p_i");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "c_i");
        inf.readEoln();

        ensuref(p != i, "node %d cannot be its own parent", i);
        parent[i] = p;
    }

    vector<int> state(n + 1, 0);
    state[1] = 2;

    for (int start = 2; start <= n; ++start) {
        if (state[start] == 2) {
            continue;
        }

        vector<int> path;
        int v = start;
        while (state[v] == 0) {
            state[v] = 1;
            path.push_back(v);
            v = parent[v];
        }

        ensuref(state[v] == 2, "parent links from node %d do not reach root 1", start);

        for (int u : path) {
            state[u] = 2;
        }
    }

    inf.readEof();
}

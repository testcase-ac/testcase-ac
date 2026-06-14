#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        parent[i] = inf.readInt(1, n, "p_i");
        ensuref(parent[i] != i, "p_%d must not be %d", i, i);
        inf.readEoln();
    }

    vector<int> state(n + 1, 0);
    state[1] = 2;
    for (int start = 2; start <= n; ++start) {
        if (state[start] == 2) {
            continue;
        }

        vector<int> path;
        int v = start;
        while (v != 1 && state[v] == 0) {
            state[v] = 1;
            path.push_back(v);
            v = parent[v];
        }

        ensuref(v == 1 || state[v] == 2,
                "parent chain from vertex %d does not reach root 1", start);

        for (int u : path) {
            state[u] = 2;
        }
    }

    inf.readEof();
}

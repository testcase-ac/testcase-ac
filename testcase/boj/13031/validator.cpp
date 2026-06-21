#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // CHECK: the statement has a typo saying 1 <= N <= 1e9 for a_i; interpret it as 1 <= a_i <= 1e9.
    inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    parent[1] = 1;
    for (int node = 2; node <= n; ++node) {
        int p = inf.readInt(1, n, "p_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "c_i");
        inf.readEoln();

        ensuref(p != node, "node %d cannot be its own parent", node);
        parent[node] = p;
    }

    const int done = -1;
    vector<int> state(n + 1, 0);
    state[1] = done;
    for (int start = 2; start <= n; ++start) {
        if (state[start] == done) {
            continue;
        }

        int v = start;
        while (state[v] == 0) {
            state[v] = start;
            v = parent[v];
        }

        ensuref(state[v] == done, "parent pointers from node %d do not reach root 1", start);

        v = start;
        while (state[v] == start) {
            state[v] = done;
            v = parent[v];
        }
    }

    inf.readEof();
    return 0;
}

#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(0, n - 1, "k");
    inf.readEoln();

    vector<int> parent(n, -1);
    parent[0] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int p = inf.readInt(0, n - 1, "p");
        inf.readSpace();
        int c = inf.readInt(0, n - 1, "c");
        inf.readEoln();

        ensuref(p != c, "edge %d has the same parent and child: %d", i + 1, p);
        ensuref(c != 0, "edge %d makes root 0 a child", i + 1);
        ensuref(parent[c] == -1, "node %d has multiple parents", c);

        parent[c] = p;
    }

    for (int v = 1; v < n; ++v) {
        ensuref(parent[v] != -1, "node %d has no parent", v);
    }

    vector<unsigned char> state(n, 0);
    state[0] = 2;
    for (int start = 1; start < n; ++start) {
        int v = start;
        while (state[v] == 0) {
            state[v] = 1;
            v = parent[v];
        }
        ensuref(state[v] == 2, "parent links from node %d do not reach root 0", start);

        v = start;
        while (state[v] == 1) {
            state[v] = 2;
            v = parent[v];
        }
    }

    inf.readInts(n, 0, 1, "a_i");
    inf.readEoln();

    inf.readEof();
}

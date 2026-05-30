#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    vector<int> state(n + 1, 0);
    for (int vertex = 2; vertex <= n; ++vertex) {
        parent[vertex] = inf.readInt(1, n, "a");
        inf.readEoln();
        ensuref(parent[vertex] != vertex,
                "vertex %d cannot be its own parent", vertex);
    }

    for (int vertex = 2; vertex <= n; ++vertex) {
        int cur = vertex;
        while (cur != 1 && state[cur] == 0) {
            state[cur] = vertex;
            cur = parent[cur];
        }
        ensuref(cur == 1 || state[cur] != vertex,
                "parent links from vertex %d do not reach root 1", vertex);
    }

    for (int query = 1; query <= q; ++query) {
        inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, n, "c");
        inf.readSpace();
        inf.readInt(0, 1, "d");
        inf.readEoln();
    }

    inf.readEof();
}

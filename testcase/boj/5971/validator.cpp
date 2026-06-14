#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    parent[1] = 1;
    for (int i = 2; i <= n; ++i) {
        parent[i] = inf.readInt(1, n, "P_i");
        inf.readEoln();
    }

    vector<int> state(n + 1, 0);
    for (int start = 1; start <= n; ++start) {
        int node = start;
        vector<int> path;
        while (state[node] == 0) {
            state[node] = start;
            path.push_back(node);
            if (node == 1) {
                break;
            }
            node = parent[node];
        }

        ensuref(node == 1 || state[node] != start,
                "parent chain from pasture %d contains a cycle not reaching root 1", start);

        for (int v : path) {
            state[v] = -1;
        }
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "B_k");
        inf.readSpace();
        inf.readInt(1, n, "J_k");
        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = findRoot(parent, parent[x]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100, "v_i");
        inf.readEoln();
    }

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);

        int rootA = findRoot(parent, a);
        int rootB = findRoot(parent, b);
        ensuref(rootA != rootB, "cycle or duplicate edge at edge %d: %d %d", i, a, b);
        parent[rootB] = rootA;
    }

    int root = findRoot(parent, 1);
    for (int i = 2; i <= n; ++i) {
        ensuref(findRoot(parent, i) == root, "node %d is disconnected from node 1", i);
    }

    inf.readEof();
}

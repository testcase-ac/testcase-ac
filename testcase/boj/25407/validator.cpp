#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 100000, "N");
    inf.readEoln();

    vector<int> degree(n + 1);
    vector<int> ancestors = {1};
    for (int node = 2; node <= n; ++node) {
        int parent = inf.readInt(1, node - 1, "p_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000000LL, "c_i");
        inf.readEoln();

        while (!ancestors.empty() && ancestors.back() != parent)
            ancestors.pop_back();
        ensuref(!ancestors.empty(),
                "node %d with parent %d does not follow preorder", node, parent);
        ancestors.push_back(node);
        ++degree[parent];
        ++degree[node];
    }
    ensuref(degree[1] >= 2, "intersection 1 has degree %d, expected at least 2",
            degree[1]);

    int leaves = 0;
    for (int node = 1; node <= n; ++node)
        leaves += degree[node] == 1;
    for (int i = 0; i < leaves; ++i) {
        if (i)
            inf.readSpace();
        inf.readLong(0LL, 1000000000000LL, "w_i");
    }
    inf.readEoln();

    int q = inf.readInt(1, 250000, "Q");
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        ensuref(u != v, "query %d uses the same intersection %d twice", i + 1, u);
    }
    inf.readEof();
}

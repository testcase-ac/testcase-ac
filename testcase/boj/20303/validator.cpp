#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 30000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 100000, "M");
    inf.readSpace();
    int K = inf.readInt(1, min(N, 3000), "K");
    inf.readEoln();

    // Read c_1 ... c_N
    vector<int> c = inf.readInts(N, 1, 10000, "c_i");
    inf.readEoln();

    // Read M edges, check for loops and multiple edges
    set<pair<int,int>> edges;
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();

        ensuref(a != b, "Loop detected at edge %d: (%d, %d)", i+1, a, b);
        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}), "Multiple edge detected at edge %d: (%d, %d)", i+1, a, b);
        edges.insert({u, v});
    }

    inf.readEof();
}

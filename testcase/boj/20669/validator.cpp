#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 20000, "M");
    inf.readSpace();
    inf.readInt(1, 1000000, "K");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "U");
        inf.readSpace();
        int v = inf.readInt(1, n, "V");
        inf.readEoln();

        ensuref(u != v, "road %d is a self-loop: %d %d", i, u, v);
    }

    int pSize = inf.readInt(1, n, "|P|");
    inf.readSpace();
    int qSize = inf.readInt(1, n, "|Q|");
    inf.readEoln();

    vector<bool> inP(n + 1, false);
    for (int i = 1; i <= pSize; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int node = inf.readInt(1, n, "P_i");
        ensuref(!inP[node], "duplicate node in P at position %d: %d", i, node);
        inP[node] = true;
    }
    inf.readEoln();

    vector<bool> inQ(n + 1, false);
    for (int i = 1; i <= qSize; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int node = inf.readInt(1, n, "Q_i");
        ensuref(!inQ[node], "duplicate node in Q at position %d: %d", i, node);
        inQ[node] = true;
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}

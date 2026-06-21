#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 14, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200, "M");
    inf.readEoln();

    vector<int> p = inf.readInts(n, 1, n, "P_i");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n + 1, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n + 1, "v_i");
        inf.readSpace();
        inf.readInt(1, 100, "w_i");
        inf.readEoln();

        ensuref(u != v, "road %d has identical endpoints: %d", i, u);
    }

    inf.readEof();
}

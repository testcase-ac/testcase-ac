#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, n, "M");
    inf.readSpace();
    int q = inf.readInt(1, 5000, "Q");
    inf.readEoln();

    vector<bool> seen(m + 1, false);
    for (int i = 1; i <= m; ++i) {
        int p = inf.readInt(1, m, "P_i");
        inf.readEoln();
        ensuref(!seen[p], "P is not a permutation: position %d appears more than once", p);
        seen[p] = true;
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "q_i");
        inf.readEoln();
    }

    inf.readEof();
}

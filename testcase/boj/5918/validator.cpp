#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<int> occupiedStalls;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, m, "X_i");
        inf.readEoln();
        ensuref(occupiedStalls.insert(x).second,
                "duplicate cow stall at index %d: %d", i, x);
    }

    for (int j = 1; j <= m; ++j) {
        inf.readInt(1, 1000000, "C_j");
        inf.readEoln();
    }

    inf.readEof();
}

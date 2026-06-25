#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    set<int> positions;
    for (int i = 1; i <= k; ++i) {
        int x = inf.readInt(1, n, "X_i");
        inf.readSpace();
        inf.readInt(0, n, "R_i");
        inf.readSpace();
        inf.readInt(1, 1000, "C_i");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "cookie positions must be distinct; duplicate X_%d=%d", i, x);
    }

    inf.readEof();
}

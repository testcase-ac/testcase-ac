#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "K1");
    inf.readSpace();
    inf.readInt(1, 1000000000, "K2");
    inf.readEoln();

    set<int> coordinates;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, 1000000000, "X_i");
        inf.readSpace();
        inf.readInt(1, n, "S_i");
        inf.readEoln();
        ensuref(coordinates.insert(x).second,
                "house coordinates must be distinct: X_%d = %d", i, x);
    }

    inf.readEof();
}

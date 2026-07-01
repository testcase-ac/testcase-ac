#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<int> bottomX;
    set<int> topX;
    for (int i = 1; i <= n; ++i) {
        int x1 = inf.readInt(0, 1000000, "X_i1");
        inf.readSpace();
        int x2 = inf.readInt(0, 1000000, "X_i2");
        inf.readEoln();

        ensuref(bottomX.insert(x1).second,
                "duplicate bottom endpoint x-coordinate at conductor %d: %d", i, x1);
        ensuref(topX.insert(x2).second,
                "duplicate top endpoint x-coordinate at conductor %d: %d", i, x2);
    }

    inf.readEof();
}

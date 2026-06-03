#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement only gives N <= 100000, but the robot list is the
    // central input object, so local policy rejects the empty instance.
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(-10000, 10000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "Y_i");
        inf.readSpace();
        inf.readInt(1, 1000, "V_i");
        inf.readEoln();

        ensuref(positions.insert({x, y}).second,
                "duplicate robot position at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}

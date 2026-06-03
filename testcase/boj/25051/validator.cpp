#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200, "M");
    inf.readEoln();

    set<pair<long long, long long>> positions;
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "X_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "Y_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000000LL, "S_i");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "star %d is at the origin", i);
        ensuref(positions.insert({x, y}).second,
                "duplicate star position at star %d: (%lld, %lld)", i, x, y);
    }

    for (int i = 1; i <= m; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000000000000LL, "P_i");
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}

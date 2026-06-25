#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    set<long long> positions;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(1LL, 1000000000LL, "X_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "V_i");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "duplicate position at picture index %d: %lld",
                i + 1,
                x);
    }

    inf.readEof();
}

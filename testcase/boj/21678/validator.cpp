#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kCoordLimit = 1000000000LL;

    int n = inf.readInt(3, 1500, "n");
    inf.readEoln();

    set<pair<long long, long long>> points;
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(-kCoordLimit, kCoordLimit, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-kCoordLimit, kCoordLimit, "y_i");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%lld, %lld)", i, x, y);
    }

    inf.readEof();
}

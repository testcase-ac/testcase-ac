#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "n");
    inf.readEoln();

    set<pair<long long, long long>> points;
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%lld, %lld)", i, x, y);
    }

    inf.readEof();
}

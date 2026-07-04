#include "testlib.h"

#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    set<pair<long long, long long>> points;
    for (int i = 0; i < m; ++i) {
        long long x = inf.readLong(0LL, 1000000000LL, "x_j");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000000000LL, "y_j");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%lld, %lld)", i + 1, x, y);
    }

    inf.readEof();
}

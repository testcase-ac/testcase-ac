#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1500, "n");
    inf.readEoln();

    set<pair<long long, long long>> points;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%lld, %lld)", i + 1, x, y);
    }

    inf.readEof();
}

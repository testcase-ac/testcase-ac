#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMinCoord = -1000000000LL;
    const long long kMaxCoord = 1000000000LL;

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    set<pair<long long, long long>> fruits;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(kMinCoord, kMaxCoord, "f_x");
        inf.readSpace();
        long long y = inf.readLong(kMinCoord, kMaxCoord, "f_y");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "fruit %d is at the origin", i + 1);
        ensuref(fruits.insert({x, y}).second,
                "duplicate fruit position at index %d: (%lld, %lld)", i + 1,
                x, y);
    }

    set<pair<long long, long long>> endpoints;
    for (int i = 0; i < m; ++i) {
        long long x = inf.readLong(kMinCoord, kMaxCoord, "e_x");
        inf.readSpace();
        long long y = inf.readLong(kMinCoord, kMaxCoord, "e_y");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "endpoint %d is at the origin", i + 1);
        ensuref(endpoints.insert({x, y}).second,
                "duplicate endpoint position at index %d: (%lld, %lld)",
                i + 1, x, y);
    }

    inf.readEof();
}

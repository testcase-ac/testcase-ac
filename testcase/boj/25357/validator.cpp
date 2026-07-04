#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long kMinCoord = -1000000000LL;
    constexpr long long kMaxCoord = 1000000000LL;

    set<pair<long long, long long>> points;
    for (int i = 0; i < 3; ++i) {
        long long x = inf.readLong(kMinCoord, kMaxCoord, "x");
        inf.readSpace();
        long long y = inf.readLong(kMinCoord, kMaxCoord, "y");
        inf.readEoln();

        ensuref(points.emplace(x, y).second, "points must be pairwise distinct: (%lld, %lld)", x, y);
    }

    inf.readEof();
}

#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<pair<long long, long long>> positions;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();

        ensuref(positions.emplace(x, y).second,
                "duplicate sheep position at index %d: (%lld, %lld)",
                i + 1,
                x,
                y);
    }

    inf.readEof();
}

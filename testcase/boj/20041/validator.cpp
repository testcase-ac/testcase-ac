#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_COORD = -1000000000LL;
    const long long MAX_COORD = 1000000000LL;

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    set<pair<long long, long long>> occupied;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(MIN_COORD, MAX_COORD, "x_i");
        inf.readSpace();
        long long y = inf.readLong(MIN_COORD, MAX_COORD, "y_i");
        inf.readEoln();

        ensuref(occupied.insert({x, y}).second,
                "duplicate police position at index %d: (%lld, %lld)",
                i + 1,
                x,
                y);
    }

    long long sx = inf.readLong(MIN_COORD, MAX_COORD, "s_x");
    inf.readSpace();
    long long sy = inf.readLong(MIN_COORD, MAX_COORD, "s_y");
    inf.readEoln();

    ensuref(!occupied.count({sx, sy}),
            "thief position duplicates a police position: (%lld, %lld)",
            sx,
            sy);

    inf.readEof();
}

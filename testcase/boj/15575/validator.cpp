#include "testlib.h"

#include <cstdint>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_COORD = -100000000;
    const int MAX_COORD = 100000000;
    const long long COORD_SPAN = 200000001LL;

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    unordered_set<long long> points;
    points.reserve(static_cast<size_t>(n) * 2);

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(MIN_COORD, MAX_COORD, "x_i");
        inf.readSpace();
        int y = inf.readInt(MIN_COORD, MAX_COORD, "y_i");
        inf.readEoln();

        long long key = (static_cast<long long>(x) - MIN_COORD) * COORD_SPAN
                      + (static_cast<long long>(y) - MIN_COORD);
        ensuref(points.insert(key).second,
                "duplicate signal at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
    return 0;
}

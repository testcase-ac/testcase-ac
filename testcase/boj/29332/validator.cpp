#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_COORD = -1000000000LL;
    const long long MAX_COORD = 1000000000LL;
    const long long NEG_INF = -4000000000000000000LL;
    const long long POS_INF = 4000000000000000000LL;

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    long long minX = NEG_INF;
    long long maxX = POS_INF;
    long long minY = NEG_INF;
    long long maxY = POS_INF;

    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(MIN_COORD, MAX_COORD, "x_i");
        inf.readSpace();
        long long y = inf.readLong(MIN_COORD, MAX_COORD, "y_i");
        inf.readSpace();
        string d = inf.readToken("[LRUD]", "d_i");
        inf.readEoln();

        if (d == "L") {
            maxX = min(maxX, x - 1);
        } else if (d == "R") {
            minX = max(minX, x + 1);
        } else if (d == "U") {
            minY = max(minY, y + 1);
        } else {
            maxY = min(maxY, y - 1);
        }
    }

    ensuref(minX <= maxX && minY <= maxY,
            "clues must leave at least one possible integer grid point");
    inf.readEof();
}

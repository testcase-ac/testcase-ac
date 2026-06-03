#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>

using namespace std;

const long long COORD_LIMIT = 1000000000LL;
const long long VALUE_LIMIT = 1000000000LL;

pair<long long, long long> normalizedDirection(long long x, long long y) {
    long long g = gcd(abs(x), abs(y));
    return {x / g, y / g};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    set<pair<long long, long long>> positions;
    pair<long long, long long> commonDirection;
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(-COORD_LIMIT, COORD_LIMIT, "balloon_x");
        inf.readSpace();
        long long y = inf.readLong(-COORD_LIMIT, COORD_LIMIT, "balloon_y");
        inf.readSpace();
        inf.readLong(1LL, VALUE_LIMIT, "hp");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "balloon %d is at the tower position", i);
        ensuref(positions.insert({x, y}).second,
                "duplicate balloon position at index %d: (%lld, %lld)", i, x, y);

        pair<long long, long long> direction = normalizedDirection(x, y);
        if (i == 1) {
            commonDirection = direction;
        } else {
            ensuref(direction == commonDirection,
                    "balloon %d is not on the common removable ray", i);
        }
    }

    for (int i = 1; i <= m; ++i) {
        // CHECK: the statement gives no separate attack-direction coordinate bounds.
        // Use the same coordinate range as balloon positions and reject the undefined
        // zero direction.
        long long x = inf.readLong(-COORD_LIMIT, COORD_LIMIT, "attack_x");
        inf.readSpace();
        long long y = inf.readLong(-COORD_LIMIT, COORD_LIMIT, "attack_y");
        inf.readSpace();
        inf.readLong(1LL, VALUE_LIMIT, "damage");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "attack %d has zero direction", i);
    }

    inf.readEof();
}

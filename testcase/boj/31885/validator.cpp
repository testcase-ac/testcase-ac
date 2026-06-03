#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_COORD = -1000000000000LL;
    const long long MAX_COORD = 1000000000000LL;

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    inf.readInt(1, 5, "k");
    inf.readEoln();

    set<pair<long long, long long>> items;
    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(MIN_COORD, MAX_COORD, "a_i");
        inf.readSpace();
        long long b = inf.readLong(MIN_COORD, MAX_COORD, "b_i");
        inf.readEoln();

        ensuref(a != 0 || b != 0, "item %d is (0, 0)", i);
        ensuref(items.insert({a, b}).second, "duplicate item at index %d: (%lld, %lld)", i, a, b);
    }

    long long ex = inf.readLong(MIN_COORD, MAX_COORD, "e_x");
    inf.readSpace();
    long long ey = inf.readLong(MIN_COORD, MAX_COORD, "e_y");
    inf.readEoln();
    ensuref(ex != 0 || ey != 0, "destination is (0, 0)");

    inf.readEof();
}

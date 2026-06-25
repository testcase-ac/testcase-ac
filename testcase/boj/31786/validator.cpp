#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long COORD_MIN = -1000000000LL;
    const long long COORD_MAX = 1000000000LL;

    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    bool hasTypeOneQuery = false;
    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            long long x = inf.readLong(1LL, COORD_MAX, "x");
            hasTypeOneQuery = true;
        } else {
            long long x = inf.readLong(COORD_MIN, COORD_MAX, "x");
            inf.readSpace();
            long long y = inf.readLong(COORD_MIN, COORD_MAX, "y");
            ensuref(y != 0, "query %d has a base station on the x-axis", i);
        }

        inf.readEoln();
    }

    ensuref(hasTypeOneQuery, "input must contain at least one type 1 query");
    inf.readEof();
}

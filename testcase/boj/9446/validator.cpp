#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    inf.readLongs(n, 0LL, 1000000000LL, "c_i");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(a != x, "crafting rule %d has a_i == x_i == %d", i, a);
        ensuref(x != y, "crafting rule %d has x_i == y_i == %d", i, x);
        ensuref(y != a, "crafting rule %d has y_i == a_i == %d", i, y);
    }

    inf.readEof();
}

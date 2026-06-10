#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readEoln();

    int a = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 1000000, "B");
    inf.readSpace();
    int c = inf.readInt(1, 1000000, "C");
    inf.readSpace();
    int d = inf.readInt(1, 1000000, "D");
    inf.readSpace();
    int e = inf.readInt(1, 1000000, "E");
    inf.readSpace();
    int f = inf.readInt(1, 1000000, "F");
    inf.readEoln();

    ensuref(a <= b, "A must be at most B: %d > %d", a, b);
    ensuref(b <= c, "B must be at most C: %d > %d", b, c);
    ensuref(c <= d, "C must be at most D: %d > %d", c, d);
    ensuref(d <= e, "D must be at most E: %d > %d", d, e);
    ensuref(e <= f, "E must be at most F: %d > %d", e, f);

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 50000000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 50000000, "B");
    inf.readSpace();
    int k = inf.readInt(1, 2000000000, "K");
    inf.readEoln();

    ensuref(a < b, "A must be less than B: A=%d, B=%d", a, b);
    ensuref(b - a <= 300, "B - A must be at most 300: A=%d, B=%d", a, b);
    (void)k;

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(0, 3000, "X");
    inf.readSpace();
    int y = inf.readInt(0, 3000, "Y");
    inf.readEoln();

    int n = x + y;
    ensuref(n >= 3, "X + Y must be at least 3, got %d", n);
    ensuref(n % 3 == 0, "X + Y must be divisible by 3, got %d", n);

    inf.readEof();
}

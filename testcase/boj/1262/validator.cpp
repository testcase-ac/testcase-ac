#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 20000, "N");
    inf.readSpace();

    int R1 = inf.readInt(0, 20000, "R1");
    inf.readSpace();

    int C1 = inf.readInt(0, 20000, "C1");
    inf.readSpace();

    int R2 = inf.readInt(0, 20000, "R2");
    inf.readSpace();

    int C2 = inf.readInt(0, 20000, "C2");

    inf.readEoln();
    inf.readEof();

    ensuref(R1 <= R2, "R1 must be <= R2");
    ensuref(C1 <= C2, "C1 must be <= C2");

    long long height = R2 - R1 + 1LL;
    long long width = C2 - C1 + 1LL;

    ensuref(height * width <= 40000, "rectangle area must be <= 40000");

    return 0;
}
#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 4000000, "A");
    inf.readSpace();
    int b = inf.readInt(a, 4000000, "B");
    inf.readSpace();
    int d = inf.readInt(0, 9, "D");
    inf.readEoln();

    // CHECK: The Korean statement gives B <= A + 2,000,000; the English
    // variant mentions the original 1,000,000 limit plus one widened case.
    ensuref(b <= a + 2000000, "B must be at most A + 2000000: A=%d, B=%d", a, b);

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int a = inf.readInt(1, 1023, "A");
        inf.readSpace();
        int b = inf.readInt(1, 1023, "B");
        inf.readEoln();

        ensuref(a != b, "A and B must differ: A=%d, B=%d", a, b);
    }

    inf.readEof();
}

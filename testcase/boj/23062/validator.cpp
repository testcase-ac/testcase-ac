#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int a_mod = inf.readInt(1, 1000000, "A");
        inf.readSpace();
        int b_mod = inf.readInt(1, 1000000, "B");
        inf.readSpace();
        int c_mod = inf.readInt(1, 1000000, "C");
        inf.readSpace();
        int a_rem = inf.readInt(0, a_mod - 1, "a");
        inf.readSpace();
        int b_rem = inf.readInt(0, b_mod - 1, "b");
        inf.readSpace();
        inf.readInt(0, c_mod - 1, "c");
        inf.readEoln();
    }

    inf.readEof();
}

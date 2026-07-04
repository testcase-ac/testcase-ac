#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 10000, "z");
    inf.readEoln();

    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 100000, "h");
        inf.readSpace();
        inf.readInt(1, 100000, "a");
        inf.readSpace();
        inf.readInt(1, 100000, "b");
        inf.readSpace();
        inf.readInt(1, 100000, "c");
        inf.readSpace();
        inf.readInt(1, 100000, "v_a");
        inf.readSpace();
        inf.readInt(1, 100000, "v_b");
        inf.readSpace();
        inf.readInt(1, 100000, "v_c");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

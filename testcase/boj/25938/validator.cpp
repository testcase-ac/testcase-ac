#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only says g is positive; cap it by local policy.
    int g = inf.readInt(1, 100000, "g");
    inf.readEoln();

    for (int tc = 1; tc <= g; ++tc) {
        setTestCase(tc);

        inf.readInt(2, 100, "d");
        inf.readSpace();
        inf.readInt(2, 100, "n");
        inf.readEoln();
    }

    inf.readEof();
}

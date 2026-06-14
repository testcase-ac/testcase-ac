#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int a = inf.readInt(1, 2000, "A");
        inf.readSpace();
        int b = inf.readInt(a, 2000, "B");
        inf.readEoln();
    }

    inf.readEof();
}

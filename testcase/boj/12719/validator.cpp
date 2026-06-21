#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 10, "C");
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        int a = inf.readInt(1, 1000, "A");
        inf.readSpace();
        int b = inf.readInt(a, 1000, "B");
        inf.readSpace();
        inf.readInt(2, b, "P");
        inf.readEoln();
    }

    inf.readEof();
}

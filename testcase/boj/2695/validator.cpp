#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        setTestCase(i);

        inf.readInt(1, 50, "B");
        inf.readSpace();
        inf.readInt(1, 1000, "M");
        inf.readEoln();
    }

    inf.readEof();
}

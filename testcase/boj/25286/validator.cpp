#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1212, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(2000, 2100, "y_i");
        inf.readSpace();
        inf.readInt(1, 12, "m_i");
        inf.readEoln();
    }

    inf.readEof();
}

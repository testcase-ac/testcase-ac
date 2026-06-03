#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int s = inf.readInt(1, 1000000000, "S");
        inf.readSpace();
        int f = inf.readInt(s, 1000000000, "F");
        inf.readEoln();
    }

    inf.readEof();
}

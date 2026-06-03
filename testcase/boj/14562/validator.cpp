#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    for (int i = 1; i <= c; ++i) {
        setTestCase(i);

        int s = inf.readInt(1, 99, "S");
        inf.readSpace();
        int t = inf.readInt(s + 1, 100, "T");
        inf.readEoln();
    }

    inf.readEof();
}

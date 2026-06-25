#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        inf.readToken("[A-Z]{1,30}", "s");
        inf.readSpace();
        inf.readToken("[A-Z]{1,30}", "t");
        inf.readEoln();
    }

    inf.readEof();
}

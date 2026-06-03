#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);
        inf.readInt(1, 11, "B");
        inf.readEoln();
    }

    inf.readEof();
}

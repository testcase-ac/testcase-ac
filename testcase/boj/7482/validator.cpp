#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);
        inf.readDouble(1.0, 1024.0, "a");
        inf.readEoln();
    }

    inf.readEof();
}

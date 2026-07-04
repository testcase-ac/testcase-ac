#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        inf.readInt(-2147483648, 2147483647, "f_1");
        inf.readSpace();
        inf.readInt(-2147483648, 2147483647, "f_f_1");
        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        inf.readLong(1LL, 123456789123LL, "N");
        inf.readEoln();
    }

    inf.readEof();
}

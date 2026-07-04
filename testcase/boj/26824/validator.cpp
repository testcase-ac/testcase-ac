#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 10000, "z");
    inf.readEoln();

    for (int i = 1; i <= z; ++i) {
        setTestCase(i);
        inf.readLong(1LL, 1000000000000000000LL, "M");
        inf.readEoln();
    }

    inf.readEof();
}

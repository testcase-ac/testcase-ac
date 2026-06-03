#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 10, "z");
    inf.readEoln();

    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();

        inf.readInts(n, 1, 1000000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}

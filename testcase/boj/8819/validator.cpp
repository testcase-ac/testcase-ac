#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 10, "Z");
    inf.readEoln();

    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);
        inf.readInt(1, 1000000, "N");
        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 10, "Z");
    inf.readEoln();

    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int w = inf.readInt(1, 1000, "W");
        inf.readSpace();
        int k = inf.readInt(1, 1000, "K");
        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int tc = 1; tc <= p; ++tc) {
        setTestCase(tc);

        // CHECK: K has no stated bound; treat it as a nonnegative dataset identifier.
        inf.readInt(0, 1000000000, "K");
        inf.readSpace();
        int n = inf.readInt(2, 100, "N");
        inf.readSpace();
        inf.readInt(0, n - 1, "v");
        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 30, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 1000, "N");
        inf.readEoln();

        int r = inf.readInt(1, 15, "R");
        inf.readEoln();

        for (int i = 0; i < r; ++i) {
            int a = inf.readInt(0, n - 1, "A");
            inf.readSpace();
            int b = inf.readInt(0, n - 1, "B");
            inf.readEoln();

            ensuref(a != b, "road %d has identical endpoints: %d", i + 1, a);
        }
    }

    inf.readEof();
}

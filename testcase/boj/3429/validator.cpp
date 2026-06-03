#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 25, "Z");
    inf.readEoln();

    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "n");
        inf.readEoln();

        inf.readLong(1LL, 1000000000LL, "h_i");
        for (int i = 2; i <= n; ++i) {
            inf.readSpace();
            inf.readLong(1LL, 1000000000LL, "h_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}

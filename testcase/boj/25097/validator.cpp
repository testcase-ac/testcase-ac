#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 1000, "N");
        inf.readSpace();
        int p = inf.readInt(2, 100, "P");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < p; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readLong(1LL, 1000000000LL, "X_i_j");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}

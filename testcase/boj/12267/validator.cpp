#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 6, "N");
        inf.readEoln();

        int side = n * n;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(1, 999, "cell");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}

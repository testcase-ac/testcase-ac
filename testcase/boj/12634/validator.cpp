#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int k = inf.readInt(2, 25, "k");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(0, 1000000, "price_i_j");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}

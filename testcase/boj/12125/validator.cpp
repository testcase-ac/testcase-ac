#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readSpace();
        // CHECK: The bundled statement sample includes M = 3, but this is the Small
        // version and the written Limits section says 1 <= M <= 2.
        int m = inf.readInt(1, 2, "M");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(-100, 100, "spell_value");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}

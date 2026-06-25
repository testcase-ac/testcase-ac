#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int large_cases = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        if (n > 100) {
            ++large_cases;
        }
        ensuref(large_cases <= 10,
                "more than 10 test cases have N > 100, first exceeded at case %d",
                tc);

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                inf.readInt(0, 10000000, "C_i_j");
                if (j < n) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
}

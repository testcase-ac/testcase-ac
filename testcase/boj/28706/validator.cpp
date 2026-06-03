#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    int total_n = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "N");
        inf.readEoln();
        total_n += n;
        ensuref(total_n <= 200000, "sum of N exceeds 200000 after testcase %d", tc);

        for (int i = 1; i <= n; ++i) {
            inf.readToken("[+*]", "op_1");
            inf.readSpace();
            inf.readInt(1, 9, "v_1");
            inf.readSpace();
            inf.readToken("[+*]", "op_2");
            inf.readSpace();
            inf.readInt(1, 9, "v_2");
            inf.readEoln();
        }
    }

    inf.readEof();
}

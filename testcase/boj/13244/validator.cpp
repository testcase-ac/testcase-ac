#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    int totalM = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        int m = inf.readInt(0, 1000000, "M");
        inf.readEoln();

        totalM += m;
        ensuref(totalM <= 1000000, "total sum of M exceeds 1000000");

        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(1, n, "B");
            inf.readEoln();

            // CHECK: The statement only bounds endpoints by 1..N; it does not state A != B.
            (void)a;
            (void)b;
        }
    }

    inf.readEof();
    return 0;
}

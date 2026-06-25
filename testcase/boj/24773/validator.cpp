#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int tc = 1; ; ++tc) {
        // CHECK: The statement gives no test case count limit; cap it by local policy.
        ensuref(tc <= 100000, "too many test cases");
        setTestCase(tc);

        int p = inf.readInt(0, 100, "p");
        inf.readSpace();
        int c = inf.readInt(0, 5000, "c");
        inf.readEoln();

        if (p == 0 && c == 0) {
            break;
        }
        ensuref(p >= 1, "p must be at least 1 before the terminator");

        for (int i = 1; i <= c; ++i) {
            int a = inf.readInt(0, p - 1, "a");
            inf.readSpace();
            int b = inf.readInt(0, p - 1, "b");
            inf.readEoln();

            ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);
        }
    }

    inf.readEof();
    return 0;
}

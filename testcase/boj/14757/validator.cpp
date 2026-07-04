#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalWork = 0;
    int testCase = 0;

    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 500000, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ++testCase;
        setTestCase(testCase);

        ensuref(n >= 1, "n must be positive before the terminator, got %d", n);
        ensuref(m >= 1, "m must be positive before the terminator, got %d", m);

        // CHECK: The statement has no total bound for multiple test cases, so cap aggregate work at one maximum-size case.
        totalWork += n + m;
        ensuref(totalWork <= 501000, "aggregate n + m is too large: %lld", totalWork);

        for (int i = 1; i <= m; ++i) {
            int d = inf.readInt(1, n, "d");
            inf.readSpace();
            int u = inf.readInt(1, n, "u");
            inf.readEoln();

            ensuref(d != u, "self relationship at edge %d: %d -> %d", i, d, u);
            // CHECK: Duplicate directed relationships are not forbidden by the statement.
        }
    }

    inf.readEof();
}

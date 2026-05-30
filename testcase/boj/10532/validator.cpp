#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 20000, "M");
    int maxDeclarations = n * n - n;
    ensuref(m <= maxDeclarations,
            "M must be at most N^2 - N; got M = %d, N = %d, limit = %d",
            m, n, maxDeclarations);
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n - 1, "A");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "B");
        inf.readEoln();
        ensuref(a != b, "member %d likes their own book at declaration %d", a, i + 1);
    }

    inf.readEof();
}

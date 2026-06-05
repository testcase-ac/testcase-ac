#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 40, "Z");
    inf.readEoln();

    int largeInstances = 0;
    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000000, "m");
        inf.readEoln();

        if (n >= 100000 || m >= 100000) {
            ++largeInstances;
            ensuref(largeInstances <= 10,
                    "more than 10 input instances have n >= 100000 or m >= 100000");
        }

        for (int i = 1; i <= m; ++i) {
            inf.readInt(0, n, "t_i");
            if (i == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}

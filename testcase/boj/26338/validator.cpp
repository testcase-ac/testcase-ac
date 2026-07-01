#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    for (int set = 1; set <= n; ++set) {
        setTestCase(set);

        int c = inf.readInt(1, 30, "c");
        inf.readEoln();

        long long sum = 0;
        for (int i = 1; i <= c; ++i) {
            long long value = inf.readLong(1LL, 1000000000LL, "package");
            sum += value;
            ensuref(sum <= 1000000000LL,
                    "sum of package values exceeds 1e9 at set %d, item %d",
                    set, i);

            if (i < c) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}

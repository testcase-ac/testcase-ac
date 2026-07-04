#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    long long palindromeLengthSum = 0;
    for (int hint = 1; hint <= m; ++hint) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(i, n, "j");
        inf.readEoln();

        if (type == 1) {
            palindromeLengthSum += j - i + 1;
            ensuref(palindromeLengthSum <= 200000,
                    "sum of type-1 interval lengths exceeds 200000 at hint %d",
                    hint);
        }
    }

    inf.readEof();
}

#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    int previousStart = 1;
    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(1, 1000000, "s");
        inf.readSpace();
        int a = inf.readInt(1, 1000000, "a");
        inf.readSpace();
        int b = inf.readInt(a, 1000000, "b");
        inf.readEoln();

        ensuref(s >= previousStart,
                "start times must be nondecreasing: hearing %d has s=%d after %d",
                i, s, previousStart);
        previousStart = s;
    }

    inf.readEof();
}

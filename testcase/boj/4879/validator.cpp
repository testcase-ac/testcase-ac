#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        int n = inf.readInt(0, 18, "n");
        inf.readSpace();
        int k = inf.readInt(0, 200, "k");
        inf.readEoln();

        if (n == 0 && k == 0) {
            ensuref(cases > 0, "input must contain at least one problem before the sentinel");
            break;
        }

        ensuref(n >= 1, "n must be between 1 and 18 for a problem line, got %d", n);
        ++cases;
    }

    inf.readEof();
}

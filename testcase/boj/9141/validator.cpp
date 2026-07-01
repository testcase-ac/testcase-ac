#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        int n = inf.readInt(0, 1500000000, "N");
        inf.readEoln();

        if (n == 0) {
            break;
        }
        ++cases;
    }

    ensuref(cases > 0, "input must contain at least one board size before 0");
    inf.readEof();
}

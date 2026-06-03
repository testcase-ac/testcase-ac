#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    while (true) {
        ++lineCount;
        ensuref(lineCount <= 50000, "input has more than 50000 lines");

        int m = inf.readInt(0, 100000, "m");
        inf.readSpace();
        int n = inf.readInt(0, 100000, "n");
        inf.readEoln();

        if (m == 0 || n == 0) {
            ensuref(m == 0 && n == 0, "terminator must be exactly 0 0");
            break;
        }

        ensuref(1 <= m && m <= 100000, "m out of range: %d", m);
        ensuref(1 <= n && n <= 100000, "n out of range: %d", n);
    }

    inf.readEof();
}

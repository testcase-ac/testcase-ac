#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int line = 1;
    while (true) {
        int n = inf.readInt(0, 1000000000, "N");
        inf.readSpace();
        int k = inf.readInt(0, 100, "K");
        inf.readEoln();

        if (n == 0 && k == 0) {
            break;
        }

        ensuref(n >= 1, "N must be positive on line %d", line);
        ensuref(k >= 1, "K must be positive on line %d", line);
        ++line;
    }

    inf.readEof();
}

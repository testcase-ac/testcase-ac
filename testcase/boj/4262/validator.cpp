#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lines = 0;
    while (true) {
        int h = inf.readInt(0, 1000001, "h");
        inf.readEoln();
        ++lines;

        if (h == 0) {
            break;
        }

        ensuref(h % 4 == 1, "h must be an H-number, got %d", h);
        // CHECK: the statement gives no number of input lines; cap keeps files practical.
        ensuref(lines <= 100000, "too many query lines: %d", lines);
    }

    inf.readEof();
}

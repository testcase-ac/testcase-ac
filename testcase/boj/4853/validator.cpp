#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    while (!inf.eof()) {
        int n = inf.readInt(2, 100, "n");
        ensuref(n % 2 == 0, "n must be even, got %d", n);
        inf.readEoln();
        ++lineCount;
    }

    ensuref(lineCount >= 1, "input must contain at least one line");
    inf.readEof();
}

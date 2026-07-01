#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int count = 0;
    while (!inf.eof()) {
        // CHECK: the statement gives one N per line until EOF but no line count.
        ensuref(count < 100000, "too many input lines");
        inf.readInt(1, 2000000000, "N");
        inf.readEoln();
        ++count;
    }

    ensuref(count > 0, "input must contain at least one N");
    inf.readEof();
}

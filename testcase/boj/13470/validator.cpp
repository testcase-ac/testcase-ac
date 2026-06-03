#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(-100000000LL, 100000000LL, "student_x");
        inf.readSpace();
        inf.readLong(-100000000LL, 100000000LL, "student_y");
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        inf.readLong(-100000000LL, 100000000LL, "tutor_x");
        inf.readSpace();
        inf.readLong(-100000000LL, 100000000LL, "tutor_y");
        inf.readEoln();
    }

    inf.readEof();
}

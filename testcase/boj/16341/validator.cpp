#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 8, "a");
    inf.readSpace();
    int b = inf.readInt(1, 8, "b");
    inf.readEoln();

    int c = inf.readInt(1, 8, "c");
    inf.readSpace();
    int d = inf.readInt(1, 8, "d");
    inf.readEoln();

    ensuref(a != c || b != d,
            "white and black knight positions must be distinct: (%d, %d)",
            a,
            b);

    inf.readEof();
}
